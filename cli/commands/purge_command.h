#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class PurgeCommand : public BaseCommand {
public:
    PurgeCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();

    WorkspaceServicePtr service;
};
