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
        .addArgWithFlagAndName('c', "clean", false, false, "Purge workspace data (docker volumes) before start")
        .end();
}

bool UpCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("up"))
        return false;
    auto vals = cmdLine.values("up");
    auto name = vals[0];
    bool clean = cmdLine.isDefined("-c");
    service->up(name, clean);
    return true;
}
