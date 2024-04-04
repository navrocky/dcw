#include "state_repository.h"

using namespace std;

static const char* CURRENT_WORKSPACE_KEY = "current-workspace";

YamlStateRepository::YamlStateRepository(const YamlConfigPtr& state)
    : state(state)
{
}

std::optional<std::string> YamlStateRepository::getCurrentWorkspace() const
{
    auto config = state->getConfig();
    auto n = config[CURRENT_WORKSPACE_KEY];
    if (n.IsDefined()) {
        return n.as<string>();
    } else {
        return std::nullopt;
    }
}

void YamlStateRepository::setCurrentWorkspace(const std::optional<std::string>& name) const
{
    auto config = state->getConfig();
    if (name.has_value()) {
        config[CURRENT_WORKSPACE_KEY] = *name;
    } else {
        config.remove(CURRENT_WORKSPACE_KEY);
    }
    state->save();
}
