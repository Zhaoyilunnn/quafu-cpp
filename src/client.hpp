#pragma once

#include "constants.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>

namespace quafu {

class Client {

public:
  void load_account();

  cpr::Response get_backends_info();

private:
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
}

cpr::Response Client::get_backends_info() {
  auto header = cpr::Header{{"api_token", _api_token}};
  auto url = cpr::Url(_website + API_BACKENDS);
  return cpr::Post(url, header);
}

} // namespace quafu
