# Create test target
add_executable(tmc_test
    "source/main.cpp"
    "source/functional/compare.cpp"
)

target_compile_features   (tmc_test PRIVATE ${TMC_COMPILE_FEATURES}              )
target_compile_options    (tmc_test PRIVATE ${TMC_TEST_COMPILER_FLAGS}           )
target_link_options       (tmc_test PRIVATE ${TMC_TEST_LINKER_FLAGS}             )
target_include_directories(tmc_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Link the main library
target_link_libraries(tmc_test too-many-containers::complete)

# Register for CTest
add_test(
    NAME tmc_test
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tmc_test --no-intro --no-path-filenames --force-colors
)