#pragma once

#include "gates.hpp"
#include <unordered_map>

namespace quafu {

class Circuit {

public:
  // Single-qubit gates
  void id(const int qubit);
  void h(const int qubit);
  void x(const int qubit);
  void y(const int qubit);
  void z(const int qubit);
  void t(const int qubit);
  void tdg(const int qubit);
  void s(const int qubit);
  void sdg(const int qubit);
  void sx(const int qubit);
  void sxdg(const int qubit);
  void sy(const int qubit);
  void sydg(const int qubit);
  void w(const int qubit);
  void sw(const int qubit);
  void rx(const int qubit, const double theta);
  void ry(const int qubit, const double theta);
  void rz(const int qubit, const double theta);
  void p(const int qubit, const double theta);

  // Multi-qubit gates
  void cnot(const int ctrl, const int targ);
  void cx(const int ctrl, const int targ);
  void cy(const int ctrl, const int targ);
  void cz(const int ctrl, const int targ);
  void cs(const int ctrl, const int targ);
  void ct(const int ctrl, const int targ);
  void cp(const int ctrl, const int targ, const double theta);
  void swap(const int q1, const int q2);
  void iswap(const int q1, const int q2);
  void toffoli(const int ctrl1, const int ctrl2, const int targ);
  void fredkin(const int ctrl, const int targ1, const int targ2);
  void xy(const int qs, const int qe, const int duration,
          const std::string &unit = "ns");
  void rxx(const int q1, const int q2, const double theta);
  void ryy(const int q1, const int q2, const double theta);
  void rzz(const int q1, const int q2, const double theta);
  void mcx(const std::vector<int> &ctrl_list, const int targ);
  void mcy(const std::vector<int> &ctrl_list, const int targ);
  void mcz(const std::vector<int> &ctrl_list, const int targ);

  // Misc
  void barrier(const std::vector<int> &qubit_list);
  void measure(const std::vector<int> &qubit_list = {},
               const std::vector<int> &cbit_list = {});

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

    for (const auto &g : _gates) {
      qasm_str += g.to_qasm() + ";\n";
    }

    for (const auto &m : measures) {
      qasm_str += "measure q[" + absl::StrCat(m.first) + "] -> meas[" +
                  absl::StrCat(m.second) + "];\n";
    }

    return qasm_str;
  }

  // Circuit attributes
  uint64_t num_qubits = 0;
  std::vector<std::pair<int, int>> measures;

private:
  std::vector<Gates> _gates{};
};

#define ADD_SINGLE_QUBIT_GATE_FUNCTION(func_name, gate_name)                   \
  void Circuit::func_name(const int qubit) {                                   \
    _gates.push_back(Gates(#gate_name, {qubit}));                              \
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

void Circuit::measure(const std::vector<int> &qubit_list,
                      const std::vector<int> &cbit_list) {
  if (qubit_list.empty() && cbit_list.empty()) {
    for (uint32_t i = 0; i < this->num_qubits; ++i) {
      this->measures.push_back(std::make_pair(i, i));
    }
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
}

} // namespace quafu
