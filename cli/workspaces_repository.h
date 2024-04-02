#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Workspace {
    std::string name;
    std::string composeFile;
};

class WorkspacesRepository {
public:
    virtual ~WorkspacesRepository() { }
    virtual void add(const Workspace& w) = 0;
    virtual void remove(const std::string& name) = 0;
    virtual std::vector<Workspace> findAll() = 0;
    virtual std::optional<Workspace> findByName(const std::string& name) = 0;
};

using WorkspacesRepositoryPtr = std::shared_ptr<WorkspacesRepository>;
