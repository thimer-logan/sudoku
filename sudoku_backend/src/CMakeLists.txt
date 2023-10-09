INCLUDE_DIRECTORIES(C:/Libraries/restbed/vcpkg/installed/x64-windows/include)
LINK_DIRECTORIES(C:/Libraries/restbed/vcpkg/installed/x64-windows/lib)

find_package(cpprestsdk CONFIG REQUIRED)

add_library(SudokuLib Board.cpp Game.cpp Cell.cpp Generator.cpp Solver.cpp DomainBoard.cpp)
target_include_directories(SudokuLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(SudokuAPI main.cpp "DomainBoard.cpp")
target_link_libraries(SudokuAPI PRIVATE SudokuLib)

target_link_libraries(SudokuAPI PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)
target_include_directories(SudokuAPI PUBLIC ${CMAKE_SOURCE_DIR}/include)