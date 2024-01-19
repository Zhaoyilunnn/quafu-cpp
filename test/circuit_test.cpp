#include "quafu/circuit.hpp"
#include "gtest/gtest.h"

const std::string SAMPLE_2Q = "OPENQASM 2.0;\n"
                              "include \"qelib1.inc\";\n"
                              "qreg q[2];\n"
                              "creg meas[2];\n"
                              "x q[0];\n"
                              "h q[1];\n"
                              "measure q[0] -> meas[0];\n"
                              "measure q[1] -> meas[1];\n";

TEST(CircuitTest, to_qasm) {
  auto qc = quafu::Circuit();
  qc.num_qubits = 2;
  qc.x(0);
  qc.h(1);
  qc.measure();
  ASSERT_EQ(qc.to_qasm(), SAMPLE_2Q);
}
