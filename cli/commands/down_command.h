#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class DownCommand : public BaseCommand {
public:
    DownCommand(const WorkspaceServicePtr& service);

    void reg(Args::CmdLine& cmdLine) override;
    bool process(const Args::CmdLine& cmdLine) override;

private:
    WorkspaceServicePtr service;
};
