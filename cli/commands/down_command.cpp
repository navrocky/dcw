#include "down_command.h"

DownCommand::DownCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void DownCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("down", Args::ValueOptions::NoValue, false, "Down current workspace")
        .addArgWithFlagAndName('p', "purge", false, false, "Purge workspace data (docker volumes)")
        .end();
}

bool DownCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("down"))
        return false;
    bool purge = cmdLine.isDefined("-p");
    service->down(purge);
    return true;
}
