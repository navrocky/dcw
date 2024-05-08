#pragma once

#include <memory>

#include "compose_executor.h"
#include "state_repository.h"
#include "workspaces_repository.h"

class WorkspaceService {
public:
    WorkspaceService(const WorkspacesRepositoryPtr& repo, const StateRepositoryPtr& stateRepo,
        const ComposeExecutorPtr& composeExecutor);

    void list(bool namesOnly);
    void add(const std::string& name, const std::string& composeFile);
    void remove(const std::string& name);
    void stop();
    void down(bool purge);
    void up(const std::string& name, bool clean);

private:
    Workspace getWorkspace(const std::string& name) const;
    std::optional<Workspace> findWorkspaceByPath(const std::string& path) const;

    WorkspacesRepositoryPtr wpRepo;
    StateRepositoryPtr stateRepo;
    ComposeExecutorPtr composeExecutor;
};

using WorkspaceServicePtr = std::shared_ptr<WorkspaceService>;
