#include "workspace_service.h"

#include <format>
#include <iostream>
#include <termcolor/termcolor.hpp>

using namespace std;
namespace tc = termcolor;

WorkspaceService::WorkspaceService(
    const WorkspacesRepositoryPtr& repo, const StateRepositoryPtr& stateRepo, const ProcessExecutorPtr& processExecutor)
    : wpRepo(repo)
    , stateRepo(stateRepo)
    , processExecutor(processExecutor)
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
        down();
    wpRepo->remove(name);
    cout << "✅ " << "Workspace \"" << tc::bold << name << tc::reset << "\" removed" << endl;
}

void WorkspaceService::down()
{
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (!currentWpName.has_value())
        return;
    auto wp = getWorkspace(currentWpName.value());
    processExecutor->exec(format("docker-compose -f {} down", wp.composeFile));
    stateRepo->setCurrentWorkspace(std::nullopt);
    cout << "✅ " << "Workspace \"" << tc::bold << *currentWpName << tc::reset << "\" stopped" << endl;
}

void WorkspaceService::up(const std::string& name)
{
    auto wp = getWorkspace(name);
    auto currentWpName = stateRepo->getCurrentWorkspace();
    if (currentWpName.has_value() && *currentWpName != name)
        down();
    processExecutor->exec(format("docker-compose -f {} up -d", wp.composeFile));
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
