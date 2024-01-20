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

## Usage

1. Set [Quafu](https://quafu.baqis.ac.cn/) API token, we have provided a binary tool to save api token in your system

```bash
# In your project dir
mkdir build && cd build
cmake .. && make
# Then there will be binary tool `quafu++` in `_deps/quafu-cpp-build/` directory
# And you can config the api token through
_deps/quafu-cpp-build/quafu++ --api-token <your-api-token>
```

2. Build quantum circuit and submit to [Quafu](https://quafu.baqis.ac.cn/) platform for execution similar to [pyquafu](https://github.com/ScQ-Cloud/pyquafu/).

```c++

#include "quafu/circuit.hpp"
#include "quafu/client.hpp"

int main(int argc, char **argv) {
  auto &client = quafu::Client::get_instance();
  client.load_account();
  client.set_backend("ScQ-P136");

  auto qc = quafu::Circuit(2);
  qc.h(0);
  qc.x(1);
  qc.measure();

  auto r = client.execute(qc.to_qasm());
  std::cout << r.counts() << std::endl;

  return 0;
}

```


## Development

```bash
bash scripts/build.sh
```
