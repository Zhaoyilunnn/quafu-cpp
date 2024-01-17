#pragma once

#include "config.hpp"
#include "utils/constants.hpp"

#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
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

  // API Definitions
  cpr::Response get_backends_info();
  cpr::Response execute(const std::string &qasm, const std::string &name = "",
                        bool async = false);

  // Configurations
  bool is_compile = false;
  bool tomo = false;
  uint32_t priority = 2;
  uint64_t shots = 1000;
  std::string backend = "ScQ-P10";

  // TODO(zhaoyilun): instantiate history?
  // std::vector<std::string> submit_history;
  // std::string runtime_job_id = "";
  // self._available_backends

private:
  Client() {}

  std::string _api_token = "";
  std::string _website = "https://quafu.baqis.ac.cn/";
};

void Client::load_account() {
  std::ifstream config(CRED_PATH);

  if (config.is_open()) {
    std::getline(config, _api_token);
    std::getline(config, _website);
    config.close();
  } else {
    // TODO(zhaoyilun): exceptions
    std::cout << "Credential file does not exist" << std::endl;
  }

  // TODO(zhaoyilun): get backends info
}

cpr::Response Client::get_backends_info() {
  auto header = cpr::Header{{"api_token", _api_token}};
  auto url = cpr::Url(_website + API_BACKENDS);
  return cpr::Post(url, header);
}

cpr::Response Client::execute(const std::string &qasm, const std::string &name,
                              bool async) {
  auto data = cpr::Payload{
      {"qtasm", qasm},
      {"shots", std::to_string(this->shots)},
      {"qubits", "1"},
      {"scan", "0"},
      {"tomo", std::to_string(static_cast<int>(this->tomo))},
      {"selected_server", "0"},
      {"compile", std::to_string(static_cast<int>(this->is_compile))},
      {"priority", std::to_string(this->priority)},
      {"task_name", name},
      {"pyquafu_version", QUAFU_VERSION},
      {"runtime_job_id", ""}};
  auto url = async ? cpr::Url{_website + API_EXEC_ASYNC}
                   : cpr::Url{_website + API_EXEC};
  auto header = cpr::Header{
      {"Content-Type", "application/x-www-form-urlencoded;charset=UTF-8"},
      {"api_token", _api_token}};
  return cpr::Post(url, header, data);
}

} // namespace quafu
