# Quafu C++ SDK

## Build and Test

```bash
mkdir -p build
cd build

# set -DBUILD_QUAFU_TEST=On To enable building unit tests
# cmake .. -DBUILD_QUAFU_TEST=On
cmake ..
make -j 8

# if built wiht unit tests
# run unit tests through `make test`
```

## Usage

### Integration with cmake

Add following configurations in your CMakeLists.txt

```cmake

include(FetchContent)
FetchContent_Declare(quafu-cpp
    GIT_REPOSITORY https://github.com/Zhaoyilunnn/quafu-cpp.git
    GIT_TAG 281e4183d27b0fb4eaca2ee7795af29e98551323) # change this to your target tag
FetchContent_MakeAvailable(quafu-cpp)

target_link_libraries(foo quafu_cpp)

```
