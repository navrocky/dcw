#pragma once

#include <optional>
#include <string>

#include "yaml_config.h"

class StateRepository {
public:
    ~StateRepository() { }
    virtual std::optional<std::string> getCurrentWorkspace() const = 0;
    virtual void setCurrentWorkspace(const std::optional<std::string>& name) const = 0;
};

using StateRepositoryPtr = std::shared_ptr<StateRepository>;

class YamlStateRepository : public StateRepository {
public:
    YamlStateRepository(const YamlConfigPtr& state);

    std::optional<std::string> getCurrentWorkspace() const override;
    void setCurrentWorkspace(const std::optional<std::string>& name) const override;

private:
    YamlConfigPtr state;
};
