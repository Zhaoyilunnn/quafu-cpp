#include "gflags/gflags.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// Define flag
DEFINE_string(api_token, "", "API Token for authentication");

int main(int argc, char *argv[]) {
  // parse command line arguments
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_api_token.empty()) {
    std::cerr << "API Token must be provided with --api-token flag."
              << std::endl;
    return 1;
  }

  // get home dir
  std::string home_dir = std::getenv("HOME");
  std::string file_path = home_dir + "/.quafu/api";

  // create directory
  std::filesystem::create_directories(
      std::filesystem::path(file_path).parent_path());

  // write api token into the directory
  std::ofstream outfile(file_path);
  if (!outfile.is_open()) {
    std::cerr << "Failed to open file: " << file_path << std::endl;
    return 1;
  }
  outfile << FLAGS_api_token << "\n"
          << "https://quafu.baqis.ac.cn/";
  outfile.close();

  std::cout << "API token has been written to " << file_path << std::endl;

  return 0;
}
