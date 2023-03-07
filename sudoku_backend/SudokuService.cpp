#include "SudokuService.h"

SudokuService::SudokuService(std::shared_ptr<IResourceFactory> resource_factory, std::shared_ptr<IServiceSettingsFactory> settings_factory) {
    _settings_factory = settings_factory;
    _service.publish(resource_factory->get_resource());
}

void SudokuService::start() {
    _service.start(_settings_factory->get_settings());
}
