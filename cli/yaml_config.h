#pragma once

#include <memory>
#include <string>
#include <yaml-cpp/yaml.h>

class YamlConfig {
public:
    YamlConfig(const std::string& file);

    void setFile(const std::string& file);

    YAML::Node& getConfig();

    void save();

private:
    bool initialized;
    std::string file;
    YAML::Node config;
};

using YamlConfigPtr = std::shared_ptr<YamlConfig>;
