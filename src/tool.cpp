#include "gflags/gflags.h"
#include "quafu/client.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// Define flag
DEFINE_string(api_token, "", "API Token for authentication");
DEFINE_string(qasm, "", "qasm file path");
DEFINE_string(backend, "ScQ-P10", "quantum system name to execute qasm");

void save_api_token() {
  // Credential file path
  std::string file_path = quafu::HOME + "/.quafu/api";

  // create directory
  std::filesystem::create_directories(
      std::filesystem::path(file_path).parent_path());

  // write api token into the directory
  std::ofstream outfile(file_path);
  if (!outfile.is_open()) {
    std::cerr << "Failed to open file: " << file_path << std::endl;
    return;
  }
  outfile << FLAGS_api_token << "\n"
          << "https://quafu.baqis.ac.cn/";
  outfile.close();

  std::cout << "API token has been written to " << file_path << std::endl;
}

void exec_qasm() {
  auto &client = quafu::Client::get_instance();
  client.load_account();
  client.set_backend(FLAGS_backend);
  std::ifstream qasm(FLAGS_qasm.c_str());
  std::stringstream buffer;

  if (qasm) {
    std::cout << "Sending " << FLAGS_qasm << " to Quafu platform" << std::endl;
    buffer << qasm.rdbuf();
    qasm.close();
    std::string qasm_str = buffer.str();
    auto r = client.execute(qasm_str);
    std::cout << r.counts() << std::endl;
  } else {
    std::cerr << "Unable to open file: " << FLAGS_qasm << std::endl;
  }
}

int main(int argc, char *argv[]) {
  // parse command line arguments
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (!FLAGS_api_token.empty()) {
    save_api_token();
  }

  if (!FLAGS_qasm.empty()) {
    exec_qasm();
  }

  return 0;
}
