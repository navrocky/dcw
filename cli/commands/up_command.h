#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class UpCommand : public BaseCommand {
public:
    UpCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();
    WorkspaceServicePtr service;
    std::string name;
    bool clean;
};
