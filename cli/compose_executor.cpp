#include "compose_executor.h"

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

void ComposeExecutorImpl::up(const std::string& file, bool detach)
{
    std::string command = format("{} -f {} up", composeCommand, file);
    if (detach)
        command += " -d";
    processExecutor->execOrThrow(command);
}

void ComposeExecutorImpl::down(const std::string& file, bool withVolumes)
{
    std::string command = format("{} -f {} down", composeCommand, file);
    if (withVolumes)
        command += " -v";
    processExecutor->execOrThrow(command);
}
