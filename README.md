# Quafu C++ SDK

`quafu-cpp` is a lightweight library for easily submission of quantum circuits to [Quafu cloud platform](https://quafu.baqis.ac.cn/)

## Prerequisite

`quafu-cpp` depends on [CPR](https://github.com/libcpr/cpr/). While CPR is automatically downloaded, you may still need to install `OpenSSL` development package, see [requirement of CPR](https://github.com/libcpr/cpr/tree/d47fd882f2da52ddcf6eef7a934d796c15623496?tab=readme-ov-file#requirements).

For example, on Ubuntu system, you could install `libssl-dev`

```
sudo apt-get update
sudo apt-get install libssl-dev
```

## Build


This project can be built and tested as follows.

```
git clone https://github.com/Zhaoyilunnn/quafu-cpp.git
cd quafu-cpp
mkdir build && cd build
cmake ..
make -j 8
```

To build unit tests

```
cmake .. -DBUILD_QUAFU_TEST=ON
make -j 8
make test
```

## Install


### CMake


Since [CMake](https://cmake.org/) v3.11, [FetchContent](https://cmake.org/cmake/help/v3.11/module/FetchContent.html) can be used to automatically download a release as a dependency at configure time.

To use `quafu-cpp` in your project, you could simply declare dependency on this library as follows.

```cmake

include(FetchContent)
FetchContent_Declare(quafu-cpp
    GIT_REPOSITORY https://github.com/Zhaoyilunnn/quafu-cpp.git
    GIT_TAG 281e4183d27b0fb4eaca2ee7795af29e98551323) # change this to your target tag
FetchContent_MakeAvailable(quafu-cpp)

# Link quafu_cpp against your project
target_link_libraries(foo quafu_cpp)

```


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

You can also directly submit your OpenQASM program to Quafu through

```bash
_deps/quafu-cpp-build/quafu++ --qasm <your-openqasm-program-file> --backend <name-of-quafu-quantum-chip>
```


## Development

```bash
bash scripts/build.sh
```
