#include <cpr/cpr.h>
#include <iostream>

#include "client.hpp"

int main(int argc, char **argv) {
  // cpr::Response r =
  // cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
  //                   cpr::Authentication{"user", "pass",
  //                   cpr::AuthMode::BASIC}, cpr::Parameters{{"anon", "true"},
  //                   {"key", "value"}});
  // std::cout << r.status_code << std::endl;                  // 200
  // std::cout << r.header["content-type"] << std::endl;       //
  // application/json; charset=utf-8 std::cout << r.text << std::endl; // JSON
  // text string

  auto client = quafu::Client();
  client.load_account();
  auto r = client.get_backends_info();
  std::cout << r.status_code << std::endl;
  std::cout << r.text << std::endl;

  return 0;
}
