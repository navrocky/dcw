#include <exception>
#include <format>
#include <iostream>

#include <args-parser/all.hpp>
#include <termcolor/termcolor.hpp>

#include "yaml_workspaces_repository.h"

#include "commands/add_command.h"
#include "commands/down_command.h"
#include "commands/list_command.h"
#include "commands/remove_command.h"
#include "commands/up_command.h"
#include "config.h"

using namespace std;
using namespace Args;
namespace tc = termcolor;

using Commands = vector<CommandPtr>;

void regCommands(const Commands& commands, CmdLine& cmdLine)
{
    for (const auto& cmd : commands) {
        cmd->reg(cmdLine);
    }
}

void processCommands(const Commands& commands, const CmdLine& cmdLine)
{
    for (const auto& cmd : commands) {
        if (cmd->process(cmdLine))
            return;
    }
    throw runtime_error("No command processed");
}

int main(int argc, char** argv)
{
    try {
        auto home = std::getenv("HOME");

        auto yamlConfig = make_shared<YamlConfig>(format("{}/.config/dcw/config.yml", home));
        auto yamlState = make_shared<YamlConfig>(format("{}/.local/share/dcw/state.yml", home));

        auto workspacesRepo = make_shared<YamlWorkspacesRepository>(yamlConfig);
        auto stateRepo = make_shared<YamlStateRepository>(yamlState);
        auto processExecutor = make_shared<ProcessExecutor>();
        auto composeExecutor = make_shared<ComposeExecutorImpl>(processExecutor);
        auto workspaceService = make_shared<WorkspaceService>(workspacesRepo, stateRepo, composeExecutor);
        Commands commands = {
            make_shared<AddCommand>(workspaceService),
            make_shared<RemoveCommand>(workspaceService),
            make_shared<ListCommand>(workspaceService),
            make_shared<UpCommand>(workspaceService),
            make_shared<DownCommand>(workspaceService),
        };

        CmdLine cmdLine(argc, argv, CmdLine::CommandIsRequired);
        cmdLine.addHelp(true, argv[0], format("Docker Compose Workspace manager (v{})", APP_VERSION));
        regCommands(commands, cmdLine);
        cmdLine.parse();
        processCommands(commands, cmdLine);
        return 0;
    } catch (const HelpHasBeenPrintedException& e) {
        return 0;
    } catch (const BaseException& e) {
        cerr << tc::red << "Call error: " << e.desc() << tc::reset << endl;
        return 1;
    } catch (const exception& e) {
        cerr << tc::red << "Error: " << e.what() << tc::reset << endl;
        return 1;
    }
}
