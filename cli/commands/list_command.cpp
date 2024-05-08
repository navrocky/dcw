#include "list_command.h"

ListCommand::ListCommand(const WorkspaceServicePtr& service)
    : service(service)
    , namesOnly(false)
{
}

void ListCommand::reg(CLI::App& app)
{
    auto cmd = app.add_subcommand("list", "List registered workspaces")
                   ->alias("l")
                   ->callback(std::bind(&ListCommand::process, this));
    cmd->add_flag("-n, --names", namesOnly, "Show names only");
}

void ListCommand::process() { service->list(namesOnly); }
