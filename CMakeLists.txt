cmake_minimum_required(VERSION 3.27)

project(quafu-cpp)


set(CMAKE_CXX_STANDARD 20)



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



##### Main project #####
set(BINTARGET quafupp)

include_directories(src)

add_executable(${BINTARGET} src/main.cpp)

target_link_libraries(${BINTARGET} PRIVATE cpr::cpr)
target_link_libraries(${BINTARGET} PRIVATE nlohmann_json::nlohmann_json)
