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
FetchContent_Declare(quafu-cpp GIT_REPOSITORY https://github.com/Zhaoyilunnn/quafu-cpp.git
                         GIT_TAG 4a99638c2d0f17c3cf6b739cba6725cf643e7b35) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(quafu-cpp)


##### Compilation settings #####
set(BIN 01_simple)

add_executable(${BIN} main.cpp)

target_link_libraries(${BIN} quafu_cpp)
