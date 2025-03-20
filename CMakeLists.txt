cmake_minimum_required(VERSION 3.28)
project(Jamfin LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)
add_executable(jamfin main.cpp)
target_compile_features(jamfin PRIVATE cxx_std_17)
target_link_libraries(jamfin PRIVATE SFML::Audio SFML::Window SFML::Graphics PkgConfig::TAGLIB)