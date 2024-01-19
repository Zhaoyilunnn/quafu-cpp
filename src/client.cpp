#include "quafu/client.hpp"

namespace quafu {

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
  _get_backends();
}

void Client::_get_backends() {
  auto header = cpr::Header{{"api_token", _api_token}};
  auto url = cpr::Url(_website + API_BACKENDS);
  auto r = cpr::Post(url, header);
  auto backends_json = nlohmann::json::parse(r.text);
  for (const auto &b : backends_json["data"]) {
    _backends.emplace(b["system_name"], b);
  }

  // TODO(): delete
  // for (auto& element : _backends) {
  //   std::cout << element.first << ": " << element.second << std::endl;
  // }
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
  return cpr::Post(url, header, data);
}
} // namespace quafu
