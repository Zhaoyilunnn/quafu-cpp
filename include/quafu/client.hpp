#pragma once

#include "config.hpp"
#include "nlohmann/json.hpp"
#include "utils/constants.hpp"

#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace quafu {

class Client {

public:
  static Client &get_instance() {
    static Client instance; // For lazy initialization
    return instance;
  }

  // Constructors
  Client(Client const &) = delete;         // Delete copy constructor
  void operator=(Client const &) = delete; // Delete assignment constructor

  // Credential managements
  void load_account();

  // List available backends
  const std::unordered_map<std::string, nlohmann::json> &backends() {
    return _backends;
  }

  // API Definitions
  cpr::Response execute(const std::string &qasm, const std::string &name = "",
                        bool async = false);

  // TODO(zhaoyilun): instantiate history?
  // std::vector<std::string> submit_history;
  // std::string runtime_job_id = "";

  // Configurations
  bool get_is_compile() const { return _is_compile; }

  void set_compile(const bool is_compile) { _is_compile = is_compile; }

  uint32_t get_priority() const { return _priority; }

  void set_priority(const uint32_t priority) { _priority = priority; }

  uint64_t get_shots() const { return _shots; }

  void set_shots(const uint64_t shots) { _shots = shots; }

  const std::string &get_backend_name() const { return _backend_name; }

  void set_backend(const std::string &backend_name) {
    if (_backends.find(backend_name) == _backends.end()) {
      // Exception handling
      std::cout << "Unsupported backend name: " << backend_name << std::endl;
      return;
    }
    _backend_name = backend_name;
  }

private:
  Client() {}

  void _get_backends();

  // Website configuration
  std::string _api_token = "";
  std::string _website = "https://quafu.baqis.ac.cn/";
  std::unordered_map<std::string, nlohmann::json> _backends;

  // Request configurations
  bool _is_compile = false;
  bool _tomo = false;
  uint32_t _priority = 2;
  uint64_t _shots = 1000;
  std::string _backend_name = "ScQ-P10";
};

} // namespace quafu
