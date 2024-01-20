#include "quafu/circuit.hpp"
#include "gtest/gtest.h"

const std::string SAMPLE_2Q_00 = "OPENQASM 2.0;\n"
                                 "include \"qelib1.inc\";\n"
                                 "qreg q[2];\n"
                                 "creg c[2];\n"
                                 "x q[0];\n"
                                 "h q[1];\n"
                                 "measure q[0] -> c[0];\n"
                                 "measure q[1] -> c[1];\n";

const std::string SAMPLE_2Q_01 = "OPENQASM 2.0;\n"
                                 "include \"qelib1.inc\";\n"
                                 "qreg q[2];\n"
                                 "creg c[2];\n"
                                 "h q[0];\n"
                                 "cx q[0],q[1];\n"
                                 "measure q[0] -> c[0];\n"
                                 "measure q[1] -> c[1];\n";

TEST(CircuitTest, to_qasm) {
  auto qc_00 = quafu::Circuit(2);
  qc_00.x(0);
  qc_00.h(1);
  qc_00.measure();
  ASSERT_EQ(qc_00.to_qasm(), SAMPLE_2Q_00);

  auto qc_01 = quafu::Circuit(2);
  qc_01.h(0);
  qc_01.cnot(0, 1);
  qc_01.measure();
  ASSERT_EQ(qc_01.to_qasm(), SAMPLE_2Q_01);
}
