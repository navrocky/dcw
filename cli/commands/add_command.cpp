#include "add_command.h"

#include <filesystem>

using namespace std;

AddCommand::AddCommand(const WorkspaceServicePtr& service)
    : service(service)
{
}

void AddCommand::reg(CLI::App& app)
{
    auto cmd = app.add_subcommand("add", "Add named docker compose file as workspace")
                   ->alias("a")
                   ->callback(std::bind(&AddCommand::process, this));
    cmd->add_option("name", name, "Workspace name")->required();
    cmd->add_option("file", file, "Docker compose file")->required();
    cmd->add_flag("-p, --create-project", createProjectFile, "Create project file in current directory");
}

void AddCommand::process()
{
    auto composeFilePath = std::filesystem::absolute(file);
    service->add(name, composeFilePath, createProjectFile);
}
