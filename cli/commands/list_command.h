#pragma once

#include "../workspace_service.h"
#include "base_command.h"

class ListCommand : public BaseCommand {
public:
    ListCommand(const WorkspaceServicePtr& service);

    void reg(CLI::App& app) override;

private:
    void process();
    WorkspaceServicePtr service;
    bool namesOnly;
};
