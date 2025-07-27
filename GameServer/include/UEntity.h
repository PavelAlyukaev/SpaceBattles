#pragma once
#include <unordered_map>
#include <memory>
#include "Interfaces.h"

class UEntity {

private:

    std::unordered_map<std::string, std::unique_ptr<IComponent>> componentPools;

public:

    template<typename T>
    void setProperty(const std::string &name, std::unique_ptr<T> component) {
        componentPools[name] = std::move(component);
    }

    template<typename T>
    T* getProperty(const std::string &name) {

        auto it = componentPools.find(name);
        return (it != componentPools.end()) ? static_cast<T*>(it->second.get()) : nullptr;
    }


    [[nodiscard]] bool hasProperty(const std::string &name) const {
        return componentPools.contains(std::string{name});
    }
};

