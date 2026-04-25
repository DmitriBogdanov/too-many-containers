cmake_minimum_required(VERSION 3.21.0...3.22.1)

project(
    TMC
    VERSION       0.2.0
    DESCRIPTION  "Comprehensive container library for C++23"
    HOMEPAGE_URL "https://github.com/DmitriBogdanov/too-many-containers"
)

# Create library target
add_library(tmc_complete INTERFACE)
add_library(tmc_detached INTERFACE)

target_include_directories(tmc_complete INTERFACE "${PROJECT_SOURCE_DIR}/include"   )
target_include_directories(tmc_complete INTERFACE "${PROJECT_SOURCE_DIR}/thirdparty")
target_include_directories(tmc_detached INTERFACE "${PROJECT_SOURCE_DIR}/include"   )

target_compile_features(tmc_complete INTERFACE cxx_std_23)
target_compile_features(tmc_detached INTERFACE cxx_std_23)

add_library(too-many-containers::complete ALIAS tmc_complete)
add_library(too-many-containers::detached ALIAS tmc_detached)

# Project is top-level => build benchmarks & tests
if("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

    include(CTest)
    enable_testing() # should be called before adding directories with tests
    
    add_subdirectory("tests")
    
endif()
