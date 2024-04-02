#include "list_command.h"

#include <iostream>
#include <termcolor/termcolor.hpp>

using namespace std;
namespace tc = termcolor;

ListCommand::ListCommand(const WorkspacesRepositoryPtr& repo)
    : repo(repo)
{
}

void ListCommand::reg(Args::CmdLine& cmdLine)
{
    cmdLine.addCommand("list", Args::ValueOptions::NoValue, false, "list registered workspaces").end();
}

bool ListCommand::process(const Args::CmdLine& cmdLine)
{
    if (!cmdLine.isDefined("list"))
        return false;
    for (const auto& wp : repo->findAll()) {
        cout << tc::bold << wp.name << tc::reset << ": " << tc::bright_grey << wp.composeFile << tc::reset << endl;
    }
    return true;
}
