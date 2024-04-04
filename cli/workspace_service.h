#pragma once

#include <memory>

#include "process_executor.h"
#include "state_repository.h"
#include "workspaces_repository.h"

class WorkspaceService {
public:
    WorkspaceService(const WorkspacesRepositoryPtr& repo, const StateRepositoryPtr& stateRepo,
        const ProcessExecutorPtr& processExecutor);

    void list(bool namesOnly);
    void add(const std::string& name, const std::string& composeFile);
    void remove(const std::string& name);
    void stop();
    void down(bool purge);
    void up(const std::string& name, bool clean);

private:
    Workspace getWorkspace(const std::string& name) const;

    WorkspacesRepositoryPtr wpRepo;
    StateRepositoryPtr stateRepo;
    ProcessExecutorPtr processExecutor;
};

using WorkspaceServicePtr = std::shared_ptr<WorkspaceService>;
