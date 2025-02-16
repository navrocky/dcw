#include "workspace_service.h"

#include <filesystem>
#include <format>
#include <iostream>
#include <termcolor/termcolor.hpp>

#include "dcw_config.h"

using namespace std;
namespace tc = termcolor;

WorkspaceService::WorkspaceService(
    const WorkspacesRepositoryPtr& repo, const StateRepositoryPtr& stateRepo, const ComposeExecutorPtr& composeExecutor)
    : wpRepo(repo)
    , stateRepo(stateRepo)
    , composeExecutor(composeExecutor)
{
}

void WorkspaceService::list(bool namesOnly)
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    for (const auto& wp : wpRepo->findAll()) {
        if (namesOnly) {
            cout << wp.name << endl;
        } else {
            if (wp.name == currentWpName)
                cout << "🟢";
            else
                cout << "⚫";
            cout << " " << tc::bold << wp.name << tc::reset << ": " << tc::bright_grey << wp.composeFile << tc::reset
                 << endl;
        }
    }
}

void WorkspaceService::add(const string& name, const string& composeFile, bool createProjectFile)
{
    Workspace wp = { .name = name, .composeFile = composeFile };
    wpRepo->add(wp);
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" added" << endl;
    if (createProjectFile) {
        auto currentDir = filesystem::current_path().string();
        wp.composeFile
            = wp.composeFile.substr(currentDir.length() + 1, wp.composeFile.length() - currentDir.length() - 1);
        DcwConfig::save(DCW_CONFIG_NAME, { .workspace = wp });
        cout << "✅ " << "Project file \"" << tc::bold << DCW_CONFIG_NAME << tc::reset << "\" created" << endl;
    }
}

void WorkspaceService::remove(const std::string& name)
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (currentWpName == name) {
        try {
            down(true);
        } catch (const std::exception& e) {
            cerr << "❌ " << "Cannot down current workspace \"" << tc::bold << name << tc::reset
                 << "\" due to error, skipping. Error is: " << tc::bright_red << e.what() << tc::reset << endl;
        }
        stateRepo->setCurrentWorkspace("");
    }
    wpRepo->remove(name);
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" removed" << endl;
}

void WorkspaceService::down(bool purge)
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (!currentWpName.has_value() || currentWpName->empty())
        return;
    auto wp = getWorkspace(currentWpName.value());
    composeExecutor->down(wp.composeFile, wp.name, purge);
    stateRepo->setCurrentWorkspace(std::nullopt);
    cout << "✅ " << "Workspace \"" << tc::bold << *currentWpName << tc::reset << "\" stopped" << endl;
    if (purge)
        cout << "✅ " << "Workspace \"" << tc::bold << *currentWpName << tc::reset << "\" data removed" << endl;
}

void WorkspaceService::up(const std::string& name, bool clean)
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    optional<Workspace> wp;

    if (!name.empty()) {
        wp = getWorkspace(name);
    }

    if (!wp.has_value()) {
        wp = loadWorkspaceFromConfig();
        if (wp) {
            auto existingWp = wpRepo->findByName(wp->name);
            if (!existingWp)
                add(wp->name, filesystem::absolute(wp->composeFile), false);
        } else {
            auto curPath = filesystem::current_path();
            wp = findWorkspaceByPath(curPath);
        }
    }

    if (!wp.has_value() && currentWpName.has_value()) {
        wp = getWorkspace(*currentWpName);
    }

    if (!wp.has_value())
        throw runtime_error("Workspace name required");

    if (currentWpName.has_value() && *currentWpName != wp->name)
        down(false);
    if (clean)
        composeExecutor->down(wp->composeFile, wp->name, true);
    try {
        composeExecutor->up(wp->composeFile, wp->name, true);
    } catch (...) {
        cerr << "❌ " << "Cannot start workspace \"" << tc::bold << wp->name << tc::reset
             << "\". Shutting down partially started containers." << endl;
        composeExecutor->down(wp->composeFile, wp->name, false);
        throw;
    }

    stateRepo->setCurrentWorkspace(wp->name);
    cout << "✅ " << "Workspace \"" << tc::bold << wp->name << tc::reset << "\" activated" << endl;
}

Workspace WorkspaceService::getWorkspace(const std::string& name) const
{
    auto wp = wpRepo->findByName(name);
    if (!wp.has_value())
        throw runtime_error(format("Workspace \"{}\" not found", name));
    return *wp;
}

std::optional<Workspace> WorkspaceService::findWorkspaceByPath(const std::string& path) const
{
    vector<Workspace> workspaces;
    for (const auto& wp : wpRepo->findAll()) {
        if (wp.composeFile.starts_with(path))
            workspaces.push_back(wp);
    }
    return workspaces.size() == 1 ? optional(workspaces[0]) : nullopt;
}

std::optional<Workspace> WorkspaceService::loadWorkspaceFromConfig()
{
    auto curPath = filesystem::current_path();
    auto configFile = DcwConfig::search(DCW_CONFIG_NAME, curPath);
    if (!configFile)
        return nullopt;

    auto config = DcwConfig::load(*configFile);
    if (filesystem::path(config.workspace.composeFile).is_relative()) {
        auto configFilePath = filesystem::path(*configFile);
        auto projectRootPath = configFilePath.has_parent_path() ? configFilePath.parent_path() : "/";
        config.workspace.composeFile = projectRootPath / config.workspace.composeFile;
    }

    return config.workspace;
}
