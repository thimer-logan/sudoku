#pragma once

#include "IService.h"
#include "IResourceFactory.h"
#include "IServiceSettingsFactory.h"

class SudokuService : public IService {

public:
    SudokuService(std::shared_ptr<IResourceFactory> resource_factory, std::shared_ptr<IServiceSettingsFactory> settings_factory);

    void start() final;

private:
    restbed::Service _service;
    std::shared_ptr<IServiceSettingsFactory> _settings_factory;
};