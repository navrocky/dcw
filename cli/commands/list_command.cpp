#include "list_command.h"

ListCommand::ListCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void ListCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("list", Args::ValueOptions::NoValue, false, "List registered workspaces")
        .addArgWithFlagAndName('n', "names", false, false, "Show names only")
        .end();
}

bool ListCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("list"))
        return false;
    bool namesOnly = cmdLine.isDefined("-n");
    service->list(namesOnly);
    return true;
}
