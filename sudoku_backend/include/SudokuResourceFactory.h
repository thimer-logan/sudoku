#pragma once

#include "IResourceFactory.h"
#include "json.hpp"
#include <vector>

class SudokuResourceFactory : public IResourceFactory {
public:
    SudokuResourceFactory();

    std::shared_ptr<restbed::Resource> get_resource() const final;

private:
    std::shared_ptr<restbed::Resource> _resource;

    void get_handler(const std::shared_ptr<restbed::Session> session);
};