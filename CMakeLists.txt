cmake_minimum_required(VERSION 3.16)
project(airy VERSION 0.1.0 LANGUAGES C)

# External Libraries
add_subdirectory(extern)

# Internal Libraries

# Final executable
add_executable(airy
    src/main.c
)
target_link_libraries(airy PRIVATE argparse)


# Tests
#if (test_build)
    #add_subdirectory(tests)
#endif()
