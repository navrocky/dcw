#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class DownCommand : public BaseCommand {
public:
    DownCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();
    WorkspaceServicePtr service;
    bool purge;
};
