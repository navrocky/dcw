#include "add_command.h"

#include <stdexcept>
#include <filesystem>

using namespace std;

AddCommand::AddCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void AddCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine
        .addCommand("add", Args::ValueOptions::ManyValues, false, "Add named docker compose file as workspace",
            string(), string(), "name> <compose file")
        .end();
}

bool AddCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("add"))
        return false;
    auto vals = cmdLine.values("add");
    if (vals.size() != 2)
        throw runtime_error("Expected two arguments for 'add' command");
    auto name = vals[0];
    auto composeFile = vals[1];
    if (name.empty())
        throw runtime_error("Name is empty");
    if (composeFile.empty())
        throw runtime_error("Compose file is empty");

    auto composeFilePath = std::filesystem::absolute(composeFile);

    service->add(name, composeFilePath);
    return true;
}
