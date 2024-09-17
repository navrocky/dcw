#include "compose_executor.h"

#include <filesystem>
#include <format>

using namespace std;

ComposeExecutorImpl::ComposeExecutorImpl(ProcessExecutorPtr processExecutor)
    : processExecutor(processExecutor)
{
    if (processExecutor->exec("docker compose --help > /dev/null") == 0)
        composeCommand = "docker compose";
    else
        composeCommand = "docker-compose";
}

void ComposeExecutorImpl::up(const std::string& file, const string& projectName, bool detach)
{
    auto dir = filesystem::path(file).parent_path();
    auto command = format("cd \"{}\" && {} -p \"{}\" -f \"{}\" up --build", dir.string(), composeCommand, projectName, file);
    if (detach)
        command += " -d";
    processExecutor->execOrThrow(command);
}

void ComposeExecutorImpl::down(const std::string& file, const string& projectName, bool withVolumes)
{
    auto command = format("{} -p \"{}\" -f \"{}\" down", composeCommand, projectName, file);
    if (withVolumes)
        command += " -v";
    processExecutor->execOrThrow(command);
}
