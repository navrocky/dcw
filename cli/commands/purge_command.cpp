#include "purge_command.h"

using namespace std;

PurgeCommand::PurgeCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void PurgeCommand::reg(CLI::App& app)
{
    app.add_subcommand("purge", "Purge data of current workspace")
        ->alias("p")
        ->callback(std::bind(&PurgeCommand::process, this));
}

void PurgeCommand::process()
{
    service->purgeCurrent();
}
