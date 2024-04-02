#include <exception>
#include <format>
#include <iostream>

#include <args-parser/all.hpp>
#include <boost/program_options.hpp>
#include <termcolor/termcolor.hpp>

#include "yaml_workspaces_repository.h"

#include "add_command.h"
#include "list_command.h"
#include "switch_command.h"

using namespace std;
using namespace Args;
namespace tc = termcolor;
namespace po = boost::program_options;

const char* DEFAULT_CONFIG_FILE = "~/.local/share/dcwm/config.yml";

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

        auto yamlConfig = make_shared<YamlConfig>(format("{}/.local/share/dcw/config.yml", home));
        auto workspacesRepo = make_shared<YamlWorkspacesRepository>(yamlConfig);
        Commands commands = {
            make_shared<AddCommand>(workspacesRepo, argv[0]),
            make_shared<ListCommand>(workspacesRepo),
            make_shared<SwitchCommand>(workspacesRepo),
        };

        CmdLine cmdLine(argc, argv, CmdLine::CommandIsRequired);
        cmdLine
            // .addCommand("remove")
            // .end()
            // .addCommand("stop")
            // .end()
            // .addCommand("down")
            // .end()
            .addHelp(true, argv[0], "Docker Compose Workspace Manager");
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
