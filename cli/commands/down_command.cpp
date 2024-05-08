#include "down_command.h"

DownCommand::DownCommand(const WorkspaceServicePtr& service)
    : service(service)
    , purge(false)
{
}

void DownCommand::reg(CLI::App& app)
{
    auto cmd = app.add_subcommand("down", "Down current workspace")
                   ->alias("d")
                   ->callback(std::bind(&DownCommand::process, this));
    cmd->add_flag("-p, --purge", purge, "Purge workspace data (docker volumes)");
}

void DownCommand::process() { service->down(purge); }
