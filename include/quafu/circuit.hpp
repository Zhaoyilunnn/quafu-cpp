#pragma once

#include "operation.hpp"
#include <unordered_map>

namespace quafu {

class Circuit {

public:
  // Constructors
  Circuit() {}
  Circuit(const uint32_t num_qubits) : _num_qubits(num_qubits) {}

  // Attribute setters and getters
  uint32_t num_qubits() const { return _num_qubits; }
  const std::vector<std::pair<uint32_t, uint32_t>> &measurements() const {
    return _measures;
  }

  // Single-qubit gates
  void id(const uint32_t qubit);
  void h(const uint32_t qubit);
  void x(const uint32_t qubit);
  void y(const uint32_t qubit);
  void z(const uint32_t qubit);
  void t(const uint32_t qubit);
  void tdg(const uint32_t qubit);
  void s(const uint32_t qubit);
  void sdg(const uint32_t qubit);
  void sx(const uint32_t qubit);
  void sxdg(const uint32_t qubit);
  void sy(const uint32_t qubit);
  void sydg(const uint32_t qubit);
  void w(const uint32_t qubit);
  void sw(const uint32_t qubit);
  void rx(const uint32_t qubit, const double theta);
  void ry(const uint32_t qubit, const double theta);
  void rz(const uint32_t qubit, const double theta);
  void p(const uint32_t qubit, const double theta);

  // Multi-qubit gates
  void cnot(const uint32_t ctrl, const uint32_t targ);
  void cx(const uint32_t ctrl, const uint32_t targ);
  void cy(const uint32_t ctrl, const uint32_t targ);
  void cz(const uint32_t ctrl, const uint32_t targ);
  void cs(const uint32_t ctrl, const uint32_t targ);
  void ct(const uint32_t ctrl, const uint32_t targ);
  void cp(const uint32_t ctrl, const uint32_t targ, const double theta);
  void swap(const uint32_t q1, const uint32_t q2);
  void iswap(const uint32_t q1, const uint32_t q2);
  void toffoli(const uint32_t ctrl1, const uint32_t ctrl2, const uint32_t targ);
  void fredkin(const uint32_t ctrl, const uint32_t targ1, const uint32_t targ2);
  void xy(const uint32_t qs, const uint32_t qe, const uint32_t duration,
          const std::string &unit = "ns");
  void rxx(const uint32_t q1, const uint32_t q2, const double theta);
  void ryy(const uint32_t q1, const uint32_t q2, const double theta);
  void rzz(const uint32_t q1, const uint32_t q2, const double theta);
  void mcx(const std::vector<uint32_t> &ctrl_list, const uint32_t targ);
  void mcy(const std::vector<uint32_t> &ctrl_list, const uint32_t targ);
  void mcz(const std::vector<uint32_t> &ctrl_list, const uint32_t targ);

  // Misc
  void barrier(const std::vector<uint32_t> &qubit_list);
  void measure(const std::vector<uint32_t> &qubit_list = {},
               const std::vector<uint32_t> &cbit_list = {});

  // TODO
  // unitary
  // delay
  // reset
  // cif

  const std::string to_qasm() const {
    std::string qasm_str = "OPENQASM 2.0;\n"
                           "include \"qelib1.inc\";\n";
    qasm_str += "qreg q[" + absl::StrCat(_num_qubits) + "];\n";
    qasm_str += "creg meas[" + absl::StrCat(_measures.size()) + "];\n";

    for (const auto &g : _ops) {
      qasm_str += g.to_qasm() + "\n";
    }

    return qasm_str;
  }

private:
  uint32_t _num_qubits = 0;                             // number of qubits
  std::vector<std::pair<uint32_t, uint32_t>> _measures; // measurements
  std::vector<Op> _ops{};                               // List of operations
};

#define ADD_SINGLE_QUBIT_FIXED_GATE(func_name, gate_name)                      \
  void Circuit::func_name(const uint32_t qubit) {                              \
    _ops.push_back(Op(#gate_name, {qubit}));                                   \
  }
ADD_SINGLE_QUBIT_FIXED_GATE(id, Id)
ADD_SINGLE_QUBIT_FIXED_GATE(h, H)
ADD_SINGLE_QUBIT_FIXED_GATE(x, X)
ADD_SINGLE_QUBIT_FIXED_GATE(y, Y)
ADD_SINGLE_QUBIT_FIXED_GATE(z, Z)
ADD_SINGLE_QUBIT_FIXED_GATE(t, T)
ADD_SINGLE_QUBIT_FIXED_GATE(tdg, Tdg)
ADD_SINGLE_QUBIT_FIXED_GATE(s, S)
ADD_SINGLE_QUBIT_FIXED_GATE(sdg, Sdg)
ADD_SINGLE_QUBIT_FIXED_GATE(sx, SX)
ADD_SINGLE_QUBIT_FIXED_GATE(sxdg, SXdg)
ADD_SINGLE_QUBIT_FIXED_GATE(sy, SY)
ADD_SINGLE_QUBIT_FIXED_GATE(sydg, SYdg)
ADD_SINGLE_QUBIT_FIXED_GATE(w, W)
ADD_SINGLE_QUBIT_FIXED_GATE(sw, SW)
#undef ADD_SINGLE_QUBIT_FIXED_GATE

#define ADD_SINGLE_QUBIT_PARAM_GATE(func_name, gate_name)                      \
  void Circuit::func_name(const uint32_t qubit, const double theta) {          \
    _ops.push_back(Op(#gate_name, {qubit}, {}, {theta}));                      \
  }
ADD_SINGLE_QUBIT_PARAM_GATE(rx, RX);
ADD_SINGLE_QUBIT_PARAM_GATE(ry, RZ);
ADD_SINGLE_QUBIT_PARAM_GATE(rz, RZ);
ADD_SINGLE_QUBIT_PARAM_GATE(p, P);
#undef ADD_SINGLE_QUBIT_PARAM_GATE

#define ADD_DOUBLE_QUBIT_FIXED_GATE(func_name, gate_name)                      \
  void Circuit::func_name(const uint32_t ctrl, const uint32_t targ) {          \
    _ops.push_back(Op(#gate_name, {ctrl, targ}));                              \
  }
ADD_DOUBLE_QUBIT_FIXED_GATE(cnot, CX);
ADD_DOUBLE_QUBIT_FIXED_GATE(cx, CX);
ADD_DOUBLE_QUBIT_FIXED_GATE(cy, CY);
ADD_DOUBLE_QUBIT_FIXED_GATE(cz, CZ);
ADD_DOUBLE_QUBIT_FIXED_GATE(cs, CS);
ADD_DOUBLE_QUBIT_FIXED_GATE(ct, CT);
#undef ADD_DOUBLE_QUBIT_FIXED_GATE
// TODO(zhaoyilun): finish other gates

void Circuit::measure(const std::vector<uint32_t> &qubit_list,
                      const std::vector<uint32_t> &cbit_list) {
  if (qubit_list.empty() && cbit_list.empty()) {
    for (uint32_t i = 0; i < _num_qubits; ++i) {
      _measures.push_back(std::make_pair(i, i));
    }
    std::vector<uint32_t> buffer(_num_qubits);
    std::iota(buffer.begin(), buffer.end(), 0);
    _ops.push_back(Op("Measure", buffer, buffer));
    return;
  }

  if (qubit_list.size() != cbit_list.size()) {
    // TODO(zhaoyilun): error handling
    std::cout << "Number of measured bits should equal to the number of "
                 "classical bits"
              << std::endl;
    return;
  }

  for (size_t i = 0; i < qubit_list.size(); ++i) {
    _measures.push_back(std::make_pair(qubit_list[i], cbit_list[i]));
  }
  _ops.push_back(Op("Measure", qubit_list, cbit_list));
}

} // namespace quafu
