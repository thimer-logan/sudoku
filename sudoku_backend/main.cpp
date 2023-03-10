#include "SudokuResourceFactory.h"
#include "SudokuServiceSettingsFactory.h"
#include "SudokuService.h"

int main (int argc, char** argv) {
    auto resource_factory = std::make_shared<SudokuResourceFactory>();
    auto settings_factory = std::make_shared<SudokuServiceSettingsFactory>();

    SudokuService service {resource_factory, settings_factory};

    service.start();

    return 0;
}