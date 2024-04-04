#include "down_command.h"

DownCommand::DownCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void DownCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("down", Args::ValueOptions::NoValue, false, "Down current workspace").end();
}

bool DownCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("down"))
        return false;

    service->down();
    return true;
}
