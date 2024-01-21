cmake_minimum_required(VERSION 3.27)


##### General settings #####
project(quafu_cpp)
set(CMAKE_CXX_STANDARD 20)
set(QUAFU_VERSION "0.4.0")

if(NOT BUILD_DIR)
    set(BUILD_DIR build)
endif()

# Use CMAKE_BINARY_DIR to make sure dependent projects can find it
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/quafu/utils/config.hpp.in ${CMAKE_BINARY_DIR}/include/config.hpp)

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

# gflags: https://gflags.github.io/gflags/#cmake
add_subdirectory(tpls/glags)


# Google test
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



##### Compilation settings #####
add_library(${PROJECT_NAME} STATIC src/dummy.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE ${QPP_LINK_DEPS} libqpp)
target_link_libraries(${PROJECT_NAME} PRIVATE absl::strings)

##### Quafu tool #####
add_executable(quafu++ src/tool.cpp)
target_link_libraries(quafu++ gflags::gflags)

##### Unit test settings #####

if (BUILD_QUAFU_TEST)
    enable_testing()

    # Gates test
    set(OP_TEST operation_test)
    set(CIRCUIT_TEST circuit_test)
    set(CLIENT_TEST client_test)
    set(RESULT_TEST result_test)

    add_executable(${OP_TEST} test/operation_test.cpp)
    add_executable(${CIRCUIT_TEST} test/circuit_test.cpp)
    add_executable(${CLIENT_TEST} test/client_test.cpp)
    add_executable(${RESULT_TEST} test/result_test.cpp)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    include_directories(${CMAKE_BINARY_DIR}/include)

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
    target_link_libraries(${CLIENT_TEST} PUBLIC cpr::cpr)
    target_link_libraries(${CLIENT_TEST} PUBLIC nlohmann_json::nlohmann_json)
    target_link_libraries(${CLIENT_TEST} PUBLIC ${QPP_LINK_DEPS} libqpp)
    target_link_libraries(${CLIENT_TEST} PUBLIC absl::strings)
    target_link_libraries(${CLIENT_TEST} PUBLIC gtest_main)
    target_link_libraries(${CLIENT_TEST} PUBLIC gmock_main)
    target_link_libraries(${CLIENT_TEST} PUBLIC ${PROJECT_NAME})
    target_link_libraries(${RESULT_TEST} PUBLIC nlohmann_json::nlohmann_json)
    target_link_libraries(${RESULT_TEST} PUBLIC gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${OP_TEST})
    gtest_discover_tests(${CIRCUIT_TEST})
    gtest_discover_tests(${CLIENT_TEST})
    gtest_discover_tests(${RESULT_TEST})
endif()
