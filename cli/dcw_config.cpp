#include "dcw_config.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

using namespace std;

const std::string DCW_CONFIG_NAME = ".dcw.yml";

namespace {

std::optional<DcwConfig> tryLoad(const std::string& file)
{
    try {
        if (!filesystem::exists(file))
            return nullopt;
        DcwConfig res;
        auto yaml = YAML::LoadFile(file);
        res.workspace.name = yaml["name"].as<string>();
        res.workspace.composeFile = yaml["composeFile"].as<string>();
        return res;
    } catch (const exception& e) {
        throw runtime_error(format("Cannot load config file \"{}\": {}", file, e.what()));
    }
}

}

void DcwConfig::save(const std::string& file, const DcwConfig& config)
{
    try {
        auto yaml = YAML::Node();
        yaml["name"] = config.workspace.name;
        yaml["composeFile"] = config.workspace.composeFile;
        std::ofstream fout(file);
        fout.exceptions(ios::badbit | ios::failbit);
        fout << "# This is a configuration file of Docker Compose Workspace (dcw) tool" << endl;
        fout << "# Read more at https://github.com/navrocky/dcw" << endl;
        fout << "" << endl;
        fout << yaml;
    } catch (const exception& e) {
        throw runtime_error(format("Cannot write config file \"{}\": {}", file, e.what()));
    }
}

std::optional<string> DcwConfig::search(const std::string& fileName, const std::string& currentDir)
{
    auto dir = filesystem::absolute(currentDir);
    while (true) {
        auto file = dir / fileName;
        if (filesystem::exists(file))
            return file.string();
        if (!dir.has_parent_path())
            return nullopt;
        dir = dir.parent_path();
    }
}

std::optional<DcwConfig> DcwConfig::searchAndLoad(const string& fileName, const std::string& currentDir)
{
    auto path = search(fileName, currentDir);
    return path ? tryLoad(*path) : nullopt;
}

DcwConfig DcwConfig::load(const std::string& file)
{
    auto res = tryLoad(file);
    if (!res)
        throw runtime_error(format("Config file \"{}\" does not exists", file));
    return *res;
}
