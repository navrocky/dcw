#include "workspace_service.h"

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
    if (currentWpName == name)
        down(true);
    wpRepo->remove(name);
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" removed" << endl;
}

void WorkspaceService::down(bool purge)
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (!currentWpName.has_value())
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
    auto wp = getWorkspace(name);
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (currentWpName.has_value() && *currentWpName != name)
        down(false);
    if (clean)
        composeExecutor->down(wp.composeFile, wp.name, true);
    try {
        composeExecutor->up(wp.composeFile, wp.name, true);
    } catch (...) {
        cerr << "❌ " << "Cannot start workspace \"" << tc::bold << name << tc::reset
             << "\". Shutting down partially started containers." << endl;
        composeExecutor->down(wp.composeFile, wp.name, false);
        throw;
    }

    stateRepo->setCurrentWorkspace(name);
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" activated" << endl;
}

Workspace WorkspaceService::getWorkspace(const std::string& name) const
{
    auto wp = wpRepo->findByName(name);
    if (!wp.has_value())
        throw runtime_error(format("Workspace \"{}\" not found", name));
    return *wp;
}
