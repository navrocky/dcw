#include <exception>
#include <format>
#include <iostream>

#include <CLI/CLI.hpp>
#include <termcolor/termcolor.hpp>

#include "yaml_workspaces_repository.h"

#include "commands/add_command.h"
#include "commands/down_command.h"
#include "commands/list_command.h"
#include "commands/remove_command.h"
#include "commands/up_command.h"
#include "config.h"

using namespace std;
namespace tc = termcolor;

using Commands = vector<CommandPtr>;

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

        if (argc == 1) {
            // if no args provided then print workspaces list
            workspaceService->list(false);
            return 0;
        }

        Commands commands = {
            make_shared<AddCommand>(workspaceService),
            make_shared<RemoveCommand>(workspaceService),
            make_shared<ListCommand>(workspaceService),
            make_shared<UpCommand>(workspaceService),
            make_shared<DownCommand>(workspaceService),
        };

        CLI::App app { format("Docker Compose Workspace manager (v{})", APP_VERSION) };
        for (const auto& cmd : commands) {
            cmd->reg(app);
        }

        CLI11_PARSE(app, argc, argv);

        return 0;
    } catch (const exception& e) {
        cerr << tc::red << "❌ Error: " << e.what() << tc::reset << endl;
        return 1;
    }
}
