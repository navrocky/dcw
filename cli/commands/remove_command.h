#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class RemoveCommand : public BaseCommand {
public:
    RemoveCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();
    WorkspaceServicePtr service;
    std::string name;
};
