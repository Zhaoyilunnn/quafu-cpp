#include "gates.hpp"
#include "gtest/gtest.h"

TEST(GateTest, to_qasm) {
  auto g = quafu::Gates();

  // Single Qubit Gates
  g.name = "X";
  g.positions = {0};
  ASSERT_EQ(g.to_qasm(), "x q[0]");

  // Multi-Qubit Gates
  g.name = "CX";
  g.positions = {1, 2};
  ASSERT_EQ(g.to_qasm(), "cx q[1],q[2]");

  // Parametrized Gates
  g.name = "RZ";
  g.positions = {3};
  g.params = {0.5};
  ASSERT_EQ(g.to_qasm(), "rz(0.5) q[3]");
}
