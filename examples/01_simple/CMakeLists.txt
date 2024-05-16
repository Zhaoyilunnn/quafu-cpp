cmake_minimum_required(VERSION 3.27)


##### General settings #####
project(01_simple)
set(CMAKE_CXX_STANDARD 20)

if(NOT BUILD_DIR)
    set(BUILD_DIR build)
endif()


##### Dependencies #####
# Add quafu-cpp to your dependency
include(FetchContent)
FetchContent_Declare(quafu-cpp
    GIT_REPOSITORY https://github.com/Zhaoyilunnn/quafu-cpp.git
    GIT_TAG main)
FetchContent_MakeAvailable(quafu-cpp)

# Python
find_package(Python REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})


##### Compilation settings #####
set(BIN 01_simple)

add_executable(${BIN} main.cpp)

target_link_libraries(${BIN} quafu_cpp)
