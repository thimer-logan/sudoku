#pragma once

#include <memory>
#include <restbed>

class IResourceFactory {
public:
    virtual std::shared_ptr<restbed::Resource> get_resource() const = 0;
};