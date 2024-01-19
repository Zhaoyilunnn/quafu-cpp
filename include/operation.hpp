#pragma once

#include <absl/strings/ascii.h>
#include <absl/strings/str_join.h>
#include <algorithm>
#include <qpp/qpp.h>
#include <string>
#include <vector>

namespace quafu {

class Op {

public:
  Op() {}
  Op(const std::string &name, const std::vector<uint32_t> &qubits,
     const std::vector<uint32_t> &clbits = {},
     const std::vector<double> &params = {})
      : name(name), qubits(qubits), clbits(clbits), params(params) {}

  const std::string to_qasm() const;

  const std::string get_symbol() const {
    if (!this->symbol.empty()) {
      return this->symbol;
    }

    auto symbol = this->name + "(";
    if (!this->params.empty()) {
      for (size_t i = 0; i < this->params.size(); ++i) {
        symbol += i == 0 ? "" : ",";
        symbol += std::to_string(this->params[i]);
      }
      symbol += ")";
      return symbol;
    }
    return this->name;
  }

  std::string name = "";
  std::string symbol = "";
  std::vector<uint32_t> clbits{};
  std::vector<uint32_t> qubits{};
  std::vector<double> params{};
};

const std::string Op::to_qasm() const {

  // Measurements
  if (0 == std::strcmp(this->name.c_str(), "Measure")) {
    // TODO(): Exception check clbits size equal qubits
    std::string qasm_str = "";
    for (size_t i = 0; i < qubits.size(); i++) {
      qasm_str += "measure q[" + absl::StrCat(this->qubits[i]) + "] -> meas[" +
                  absl::StrCat(this->clbits[i]) + "];";
      qasm_str = i == qubits.size() - 1 ? qasm_str : qasm_str + "\n";
    }
    return qasm_str;
  }

  // Gate operations
  std::string qasm_str = this->name;
  absl::AsciiStrToLower(&qasm_str);
  std::vector<std::string> str_vec;
  if (!this->params.empty()) {
    for (const auto &v : this->params) {
      str_vec.push_back(absl::StrCat(v));
    }
    qasm_str += "(" + absl::StrJoin(str_vec, ",") + ")";
  }

  qasm_str += " ";

  str_vec.clear();
  for (const auto &p : this->qubits) {
    str_vec.push_back("q[" + absl::StrCat(p) + "]");
  }
  qasm_str += absl::StrJoin(str_vec, ",") + ";";
  return qasm_str;
}

} // namespace quafu
