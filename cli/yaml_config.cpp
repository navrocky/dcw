#include "yaml_config.h"

#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

YamlConfig::YamlConfig(const std::string& file)
    : initialized(false)
    , file(file)
{
}

void YamlConfig::setFile(const std::string& file)
{
    initialized = false;
    this->file = file;
}

YAML::Node& YamlConfig::getConfig()
{
    if (!initialized) {
        if (std::filesystem::exists(file)) {
            config = YAML::LoadFile(file);
        } else {
            config = YAML::Node();
        }
        initialized = true;
    }
    return config;
}

void YamlConfig::save()
{
    if (!initialized)
        return;
    std::filesystem::create_directories(std::filesystem::path(file).parent_path());
    std::ofstream fout(file);
    fout << config;
}
