#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class AddCommand : public BaseCommand {
public:
    AddCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();

    WorkspaceServicePtr service;
    std::string name;
    std::string file;
    bool createProjectFile;
};
