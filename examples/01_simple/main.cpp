#include <iostream>

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
  std::cout << r.status_code << std::endl;
  std::cout << r.text << std::endl;

  if (argc > 1) {
    std::string qasm_path = argv[1];
    std::ifstream qasm(qasm_path);
    std::stringstream buffer;

    if (qasm) {
      buffer << qasm.rdbuf();
      qasm.close();
      std::string qasm_str = buffer.str();
      auto r = client.execute(qasm_str);
      std::cout << r.status_code << std::endl;
      std::cout << r.text << std::endl;
    } else {
      std::cerr << "Unable to open file: " << argv[1] << std::endl;
    }
  }

  // auto r = client.get_backends_info();
  // std::cout << r.status_code << std::endl;
  // std::cout << r.text << std::endl;

  return 0;
}
