cmake_minimum_required(VERSION 3.16)
project(CVPuzzleSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenMP is used (can be not found on macos) for algorithm speedup via CPU multi-core parallelism, f.e.:
#
# #pragma omp parallel for
# for (int i = 0; i < n; ++i) {
#     ... // in such way inner part of code will be executed in parallel
# }
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    message(STATUS "Looking for OpenMP - found")
else()
    message(STATUS "Looking for OpenMP - not found")
endif()

include(CTest)
if (BUILD_TESTING)
    # Keep gtest lightweight
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

    # MSVC: avoid CRT mismatch
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(third_party/googletest)
endif ()

add_subdirectory(third_party/stb)
add_subdirectory(libs/base)
add_subdirectory(libs/images)
add_subdirectory(src)
