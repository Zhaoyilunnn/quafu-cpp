#include "quafu/circuit.hpp"
#include "quafu/client.hpp"
#include <iostream>

int main() {
  auto &client = quafu::Client::get_instance();
  client.load_account();
  client.set_backend("Baiwang");

  auto qc = quafu::Circuit(2);
  qc.h(0);
  qc.cnot(0, 1);
  qc.measure();
  qc.draw_circuit();
  std::cout << qc.to_qasm() << std::endl;
  // auto r = client.execute(qc.to_qasm());
  // std::cout << r.counts() << std::endl;
  return 0;
}
