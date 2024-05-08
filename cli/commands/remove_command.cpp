#include "remove_command.h"

RemoveCommand::RemoveCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void RemoveCommand::reg(CLI::App& app)
{
    auto cmd
        = app.add_subcommand("rm", "Remove workspace")->alias("r")->callback(std::bind(&RemoveCommand::process, this));
    cmd->add_option("name", name, "Name of the workspace");
}

void RemoveCommand::process() { service->remove(name); }
