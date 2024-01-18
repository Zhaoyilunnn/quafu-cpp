#pragma once

#include "operation.hpp"
#include <unordered_map>

namespace quafu {

class Circuit {

public:
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
    qasm_str += "qreg q[" + absl::StrCat(this->num_qubits) + "];\n";
    qasm_str += "creg meas[" + absl::StrCat(this->measures.size()) + "];\n";

    for (const auto &g : _ops) {
      qasm_str += g.to_qasm() + "\n";
    }

    // for (const auto &m : measures) {
    //   qasm_str += "measure q[" + absl::StrCat(m.first) + "] -> meas[" +
    //               absl::StrCat(m.second) + "];\n";
    // }

    return qasm_str;
  }

  // Circuit attributes
  uint32_t num_qubits = 0;
  std::vector<std::pair<uint32_t, uint32_t>> measures;

private:
  std::vector<Op> _ops{};
};

#define ADD_SINGLE_QUBIT_GATE_FUNCTION(func_name, gate_name)                   \
  void Circuit::func_name(const uint32_t qubit) {                              \
    _ops.push_back(Op(#gate_name, {qubit}));                                   \
  }

ADD_SINGLE_QUBIT_GATE_FUNCTION(id, Id)
ADD_SINGLE_QUBIT_GATE_FUNCTION(h, H)
ADD_SINGLE_QUBIT_GATE_FUNCTION(x, X)
ADD_SINGLE_QUBIT_GATE_FUNCTION(y, Y)
ADD_SINGLE_QUBIT_GATE_FUNCTION(z, Z)
ADD_SINGLE_QUBIT_GATE_FUNCTION(t, T)
ADD_SINGLE_QUBIT_GATE_FUNCTION(tdg, Tdg)
ADD_SINGLE_QUBIT_GATE_FUNCTION(s, S)
ADD_SINGLE_QUBIT_GATE_FUNCTION(sdg, Sdg)
ADD_SINGLE_QUBIT_GATE_FUNCTION(sx, SX)
ADD_SINGLE_QUBIT_GATE_FUNCTION(sxdg, SXdg)
ADD_SINGLE_QUBIT_GATE_FUNCTION(w, W)
ADD_SINGLE_QUBIT_GATE_FUNCTION(sw, SW)

#undef ADD_SINGLE_QUBIT_GATE_FUNCTION

// TODO(zhaoyilun): finish other gates

void Circuit::measure(const std::vector<uint32_t> &qubit_list,
                      const std::vector<uint32_t> &cbit_list) {
  if (qubit_list.empty() && cbit_list.empty()) {
    for (uint32_t i = 0; i < this->num_qubits; ++i) {
      this->measures.push_back(std::make_pair(i, i));
    }
    std::vector<uint32_t> buffer(this->num_qubits);
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
    this->measures.push_back(std::make_pair(qubit_list[i], cbit_list[i]));
  }
  _ops.push_back(Op("Measure", qubit_list, cbit_list));
}

} // namespace quafu
