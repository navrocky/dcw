#include "yaml_workspaces_repository.h"

#include <stdexcept>

#include <format>

using namespace std;

const char* WORKSPACES_KEY = "workspaces";
const char* COMPOSE_FILE_KEY = "compose-file";

YamlWorkspacesRepository::YamlWorkspacesRepository(const YamlConfigPtr& file)
    : file(file)
{
}

void YamlWorkspacesRepository::add(const Workspace& w)
{
    auto existing = findByName(w.name);
    if (existing)
        throw runtime_error(format("Workspace with name '{}' already exists", w.name));

    auto& config = file->getConfig();
    YAML::Node wp;
    wp[COMPOSE_FILE_KEY] = w.composeFile;
    config[WORKSPACES_KEY][w.name] = wp;
    file->save();
}

void YamlWorkspacesRepository::remove(const std::string& name) { }

std::vector<Workspace> YamlWorkspacesRepository::findAll()
{
    auto& config = file->getConfig();
    auto wp = config[WORKSPACES_KEY];
    if (!wp.IsMap())
        throw runtime_error("Workspaces is not a map");

    std::vector<Workspace> result;
    for (const auto& pair : wp) {
        result.push_back(
            { .name = pair.first.as<string>(), .composeFile = pair.second[COMPOSE_FILE_KEY].as<string>() });
    }
    return result;
}

std::optional<Workspace> YamlWorkspacesRepository::findByName(const std::string& name)
{
    auto& config = file->getConfig();
    auto wp = config[WORKSPACES_KEY][name];
    if (!wp.IsDefined())
        return std::nullopt;
    return Workspace { .name = name, .composeFile = wp[COMPOSE_FILE_KEY].as<string>() };
}
