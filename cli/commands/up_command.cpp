#include "up_command.h"

UpCommand::UpCommand(const WorkspaceServicePtr& service)
    : service(service)
    , clean(false)
{
}

void UpCommand::reg(CLI::App& app)
{
    auto cmd = app.add_subcommand("up", "Switch to the workspace")
                   ->alias("u")
                   ->callback(std::bind(&UpCommand::process, this));
    cmd->add_option("name", name, "Workspace name");
    cmd->add_flag("-c, --clean", clean, "Purge workspace data (docker volumes) before start");
}

void UpCommand::process() { service->up(name, clean); }
