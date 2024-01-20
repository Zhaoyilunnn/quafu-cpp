#pragma once

#include "config.hpp"
#include "nlohmann/json.hpp"
#include "quafu/exceptions.hpp"
#include "utils/constants.hpp"

#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace quafu {

class ICprWrapper {
public:
  virtual ~ICprWrapper() = default;
  virtual cpr::Response Post(const cpr::Url &url,
                             const cpr::Header &header) = 0;
};

class CprWrapper : public ICprWrapper {
public:
  cpr::Response Post(const cpr::Url &url, const cpr::Header &header) override {
    return cpr::Post(url, header);
  }
};

class Client {

public:
  static Client &get_instance() {
    static Client instance; // For lazy initialization
    instance.set_cpr_wrapper(std::make_shared<CprWrapper>());
    return instance;
  }

  // Constructors
  Client(Client const &) = delete;         // Delete copy constructor
  void operator=(Client const &) = delete; // Delete assignment constructor

  // Set cpr wrapper, mainly used for unit test
  void set_cpr_wrapper(const std::shared_ptr<ICprWrapper> &cpr_wrapper) {
    _cpr_wrapper = cpr_wrapper;
  }

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

  // Wrapper of CPR
  std::shared_ptr<ICprWrapper> _cpr_wrapper = nullptr;

  // Call website to get quantum backends information
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

void Client::load_account() {
  std::ifstream config(CRED_PATH);

  // Load api token and website configuration
  if (config.is_open()) {
    std::getline(config, _api_token);
    std::getline(config, _website);
    config.close();
  } else {
    throw Exception(
        "Failed to open credential file, please config through quafu++");
  }

  // Fetch available backends information from website
  _get_backends();
}

void Client::_get_backends() {
  auto header = cpr::Header{{"api_token", _api_token}};
  auto url = cpr::Url(_website + API_BACKENDS);
  // auto r = cpr::Post(url, header);
  auto r = _cpr_wrapper->Post(url, header);
  auto backends_json = nlohmann::json::parse(r.text);
  for (const auto &b : backends_json["data"]) {
    _backends.emplace(b["system_name"], b);
  }
}

cpr::Response Client::execute(const std::string &qasm, const std::string &name,
                              bool async) {
  auto backend = _backends[_backend_name];
  auto data = cpr::Payload{
      {"qtasm", qasm},
      {"shots", std::to_string(this->_shots)},
      {"qubits", "1"},
      {"scan", "0"},
      {"tomo", std::to_string(static_cast<int>(this->_tomo))},
      {"selected_server",
       std::to_string(static_cast<int>(backend["system_id"]))},
      {"compile", std::to_string(static_cast<int>(this->_is_compile))},
      {"priority", std::to_string(this->_priority)},
      {"task_name", name},
      {"pyquafu_version", QUAFU_VERSION},
      {"runtime_job_id", ""}};
  auto url = async ? cpr::Url{_website + API_EXEC_ASYNC}
                   : cpr::Url{_website + API_EXEC};
  auto header = cpr::Header{
      {"Content-Type", "application/x-www-form-urlencoded;charset=UTF-8"},
      {"api_token", _api_token}};
  // FIXME(): use cpr wrapper
  return cpr::Post(url, header, data);
}

} // namespace quafu
