cmake_minimum_required(VERSION 3.0.0)
project(SudokuAPI VERSION 0.1.0)

INCLUDE_DIRECTORIES(C:/Libraries/restbed/vcpkg/installed/x86-windows/include)
LINK_DIRECTORIES(C:/Libraries/restbed/vcpkg/installed/x86-windows/lib)
find_package(unofficial-restbed CONFIG REQUIRED)

add_executable(SudokuAPI 
    main.cpp 
    SudokuResourceFactory.cpp
    SudokuService.cpp
    SudokuServiceSettingsFactory.cpp)

target_link_libraries(SudokuAPI PRIVATE unofficial::restbed::restbed)
target_include_directories(SudokuAPI PUBLIC ${CMAKE_SOURCE_DIR}/include)
