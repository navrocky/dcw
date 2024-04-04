#include "remove_command.h"

#include <stdexcept>

using namespace std;

RemoveCommand::RemoveCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void RemoveCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("rm", Args::ValueOptions::OneValue, false, "Remove workspace by name", "", "", "name").end();
}

bool RemoveCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("rm"))
        return false;
    auto name = cmdLine.value("rm");
    if (name.empty())
        throw runtime_error("Name is empty");
    service->remove(name);
    return true;
}
