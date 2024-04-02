#pragma once

#include "workspaces_repository.h"
#include "yaml_config.h"

class YamlWorkspacesRepository : public WorkspacesRepository {
public:
    YamlWorkspacesRepository(const YamlConfigPtr& file);
    void add(const Workspace& w) override;
    void remove(const std::string& name) override;
    std::vector<Workspace> findAll() override;
    std::optional<Workspace> findByName(const std::string& name) override;
private:
    YamlConfigPtr file;
};
