cmake_minimum_required(VERSION 3.10)

project(MaxFlow
        VERSION 2022.10
        DESCRIPTION "The CLI for solve traffic distribution"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to `Debug` as none was specified.")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# People keep running CMake in the wrong folder, completely nuking their project or creating weird bugs.
# This checks if you're running CMake from a folder that already has CMakeLists.txt.
# Importantly, this catches the common case of running it from the root directory.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if (EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif ()

add_subdirectory(external/json)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/maxflow.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/json/include)
target_link_directories(${PROJECT_NAME} 
    PUBLIC external/json/src)