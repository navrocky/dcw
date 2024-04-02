#pragma once

#include "base_command.h"
#include "workspaces_repository.h"

class AddCommand : public BaseCommand {
public:
    AddCommand(const WorkspacesRepositoryPtr& repo, const std::string& executableFile);

    void reg(Args::CmdLine& cmdLine) override;
    bool process(const Args::CmdLine& cmdLine) override;

private:
    std::string executableFile;
    WorkspacesRepositoryPtr repo;
};
