cmake_minimum_required(VERSION 3.27)


##### General settings #####
project(quafu-cpp)
set(CMAKE_CXX_STANDARD 20)
set(QUAFU_VERSION "0.4.0")
set(LIB_DIR src)
set(UTIL_DIR src/utils)

if(NOT BUILD_DIR)
    set(BUILD_DIR build)
endif()

configure_file(${UTIL_DIR}/config.hpp.in ${UTIL_DIR}/config.hpp)


##### Dependencies #####
# CPR
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)


# nlohmann-json
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)



##### Compilation settings #####
set(BINTARGET quafupp)

include_directories(${LIB_DIR})
include_directories(${BUILD_DIR}/src/utils)

add_executable(${BINTARGET} src/main.cpp)

target_link_libraries(${BINTARGET} PRIVATE cpr::cpr)
target_link_libraries(${BINTARGET} PRIVATE nlohmann_json::nlohmann_json)
