#include "switch_command.h"

SwitchCommand::SwitchCommand(const WorkspacesRepositoryPtr& repo)
    : repo(repo)
{
}

void SwitchCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("switch", Args::ValueOptions::OneValue, false, "switch to workspace").end();
}

bool SwitchCommand::process(const Args::CmdLine& cmdLine) { return false; }
