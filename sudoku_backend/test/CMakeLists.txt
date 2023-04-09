
include_directories(C:/Libraries/restbed/vcpkg/installed/x64-windows/include)
LINK_DIRECTORIES(C:/Libraries/restbed/vcpkg/installed/x64-windows/lib)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)  # link Boost Static libraries

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable (BoardTest boardtest.cpp)
target_link_libraries   (BoardTest
                        SudokuLib
                        Boost::unit_test_framework)

target_include_directories(BoardTest PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(BoardTest
  PRIVATE
    BOOST_TEST_DYN_LINK
  )

enable_testing()

add_test(
  NAME BoardTest
  COMMAND $<TARGET_FILE:BoardTest>
  )

add_executable (GeneratorTest "generatortest.cpp")
target_link_libraries   (GeneratorTest
                        SudokuLib
                        Boost::unit_test_framework)

target_include_directories(GeneratorTest PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(GeneratorTest
  PRIVATE
    BOOST_TEST_DYN_LINK
  )

enable_testing()

add_test(
  NAME GeneratorTest
  COMMAND $<TARGET_FILE:GeneratorTest>
  )