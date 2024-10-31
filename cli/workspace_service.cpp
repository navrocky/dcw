#include "workspace_service.h"

#include <filesystem>
#include <format>
#include <iostream>
#include <termcolor/termcolor.hpp>

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

void WorkspaceService::add(const string& name, const string& composeFile)
{
    wpRepo->add({ .name = name, .composeFile = composeFile });
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" added" << endl;
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
        auto curPath = filesystem::current_path();
        wp = findWorkspaceByPath(curPath);
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
