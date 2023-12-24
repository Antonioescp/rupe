CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

add_library(compiler_options INTERFACE)
add_library(compiler_features INTERFACE)

project(rupe)

target_compile_features(compiler_features INTERFACE cxx_std_20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(compiler_options INTERFACE /W4 /WX /Z)
else ()
    target_compile_options(compiler_options INTERFACE -Wall -Wextra -Werror -pedantic)
endif ()

add_library(RupeLib STATIC
        include/math/Vector3.hpp
        include/math/Concepts.hpp
        src/physics/Particle.cpp
        include/physics/Particle.hpp)

set_target_properties(RupeLib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(RupeLib PRIVATE compiler_features compiler_options)
target_include_directories(RupeLib PUBLIC ./include)

enable_testing()

file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/tests/**/*.test.cpp)

find_package(GTest CONFIG REQUIRED)
add_executable(RupeTest ${TEST_FILES})
target_link_libraries(RupeTest RupeLib GTest::gtest_main compiler_features compiler_options)

include(GoogleTest)
gtest_discover_tests(RupeTest)