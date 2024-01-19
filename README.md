# Quafu C++ SDK

## Integration

### CMake

Since CMake v3.11, [FetchContent](https://cmake.org/cmake/help/v3.11/module/FetchContent.html) can be used to automatically download a release as a dependency at configure time.

Example
```cmake

include(FetchContent)
FetchContent_Declare(quafu-cpp
    GIT_REPOSITORY https://github.com/Zhaoyilunnn/quafu-cpp.git
    GIT_TAG 281e4183d27b0fb4eaca2ee7795af29e98551323) # change this to your target tag
FetchContent_MakeAvailable(quafu-cpp)

# Link quafu_cpp against your project
target_link_libraries(foo quafu_cpp)

```

To build unit tests of quafu_cpp, use `-DQUAFU_BUILD_TEST=On`.

Please also refer to [01_Simple](https://github.com/Zhaoyilunnn/quafu-cpp/tree/main/examples/01_simple).

## Build

```bash
bash scripts/build.sh
```
