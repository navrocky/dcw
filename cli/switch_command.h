#pragma once

#include "base_command.h"
#include "workspaces_repository.h"

class SwitchCommand : public BaseCommand {
public:
    SwitchCommand(const WorkspacesRepositoryPtr& repo);

    void reg(Args::CmdLine& cmdLine) override;
    bool process(const Args::CmdLine& cmdLine) override;

private:
    WorkspacesRepositoryPtr repo;
};
