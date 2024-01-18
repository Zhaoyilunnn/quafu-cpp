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
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# absl
FetchContent_Declare(abseil-cpp URL https://github.com/abseil/abseil-cpp/archive/refs/tags/20230802.1.zip)
FetchContent_MakeAvailable(abseil-cpp)


# Quantum++: https://github.com/softwareQinc/qpp/blob/main/INSTALL.md
find_package(qpp REQUIRED)


# Google test
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



##### Compilation settings #####
set(BIN quafu++)

include_directories(${LIB_DIR})
include_directories(${BUILD_DIR}/src/utils)

add_executable(${BIN} src/main.cpp)

target_link_libraries(${BIN} PUBLIC cpr::cpr)
target_link_libraries(${BIN} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${BIN} PUBLIC ${QPP_LINK_DEPS} libqpp)
target_link_libraries(${BIN} PUBLIC absl::strings)



##### Unit test settings #####
enable_testing()


# Gates test
set(OP_TEST operation_test)
set(CIRCUIT_TEST circuit_test)

add_executable(${OP_TEST} test/operation_test.cpp)
add_executable(${CIRCUIT_TEST} test/circuit_test.cpp)

target_link_libraries(${OP_TEST} PUBLIC cpr::cpr)
target_link_libraries(${OP_TEST} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${OP_TEST} PUBLIC ${QPP_LINK_DEPS} libqpp)
target_link_libraries(${OP_TEST} PUBLIC absl::strings)
target_link_libraries(${OP_TEST} PUBLIC gtest_main)
target_link_libraries(${CIRCUIT_TEST} PUBLIC cpr::cpr)
target_link_libraries(${CIRCUIT_TEST} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${CIRCUIT_TEST} PUBLIC ${QPP_LINK_DEPS} libqpp)
target_link_libraries(${CIRCUIT_TEST} PUBLIC absl::strings)
target_link_libraries(${CIRCUIT_TEST} PUBLIC gtest_main)


include(GoogleTest)
gtest_discover_tests(${OP_TEST})
gtest_discover_tests(${CIRCUIT_TEST})
