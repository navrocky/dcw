#include "up_command.h"

UpCommand::UpCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void UpCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine
        .addCommand(
            "up", Args::ValueOptions::OneValue, false, "Switch to the workspace with a name", "", "default", "name")
        .end();
}

bool UpCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("up"))
        return false;
    auto vals = cmdLine.values("up");
    auto name = vals[0];
    service->up(name);
    return true;
}
