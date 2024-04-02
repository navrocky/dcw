#include "add_command.h"

#include <format>
#include <stdexcept>

using namespace std;

AddCommand::AddCommand(const WorkspacesRepositoryPtr& repo, const string& executableFile)
    : executableFile(executableFile)
    , repo(repo)
{
}

void AddCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine
        .addCommand("add", Args::ValueOptions::ManyValues, false,
            std::format("add named docker-compose as workspace. Example: {0} add my ~/projects/my/docker-compose.yml",
                executableFile))
        .end();
}

bool AddCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("add")) return false;
    auto vals = cmdLine.values("add");
    if (vals.size() != 2)
        throw runtime_error("Expected two arguments for 'add' command");
    auto name = vals[0];
    auto composeFile = vals[1];
    if (name.empty())
        throw runtime_error("Name is empty");
    if (composeFile.empty())
        throw runtime_error("Compose file is empty");

    repo->add({ .name = name, .composeFile = composeFile });
    return true;
}
