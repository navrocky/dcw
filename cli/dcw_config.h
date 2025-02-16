#pragma once

#include <optional>
#include <string>

#include "workspace.h"

extern const std::string DCW_CONFIG_NAME;

struct DcwConfig {

    Workspace workspace;

    static void save(const std::string& file, const DcwConfig& config);
    static std::optional<std::string> search(const std::string& fileName, const std::string& currentDir);
    static std::optional<DcwConfig> searchAndLoad(const std::string& fileName, const std::string& currentDir);
    static DcwConfig load(const std::string& file);
};
