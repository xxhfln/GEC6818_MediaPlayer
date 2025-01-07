cmake_minimum_required(VERSION 3.22)
project(final_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fix issues in MSVC
if (MSVC)
    add_compile_options("/utf-8")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/include)

# Find all file
file(GLOB_RECURSE SOURCES src/*.h src/*.hpp src/*.cpp src/*c)

# Compile to a executable
add_executable(${PROJECT_NAME} ${SOURCES})