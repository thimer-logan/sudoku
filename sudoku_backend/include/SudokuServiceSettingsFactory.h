#pragma once

#include "IServiceSettingsFactory.h"

class SudokuServiceSettingsFactory : public IServiceSettingsFactory {
public:
    SudokuServiceSettingsFactory();

    std::shared_ptr<restbed::Settings> get_settings() const final;

private:
    std::shared_ptr<restbed::Settings> _settings;
};