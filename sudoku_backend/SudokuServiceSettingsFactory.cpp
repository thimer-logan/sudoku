#include "SudokuServiceSettingsFactory.h"

SudokuServiceSettingsFactory::SudokuServiceSettingsFactory() {
    _settings = std::make_shared<restbed::Settings>();
    _settings->set_port(8080);
    _settings->set_default_header("Connection", "close");
    _settings->set_default_header("Access-Control-Allow-Origin", "*");
}

std::shared_ptr<restbed::Settings> SudokuServiceSettingsFactory::get_settings() const {
    return _settings;
}
