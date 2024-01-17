#pragma once

#include <absl/strings/ascii.h>
#include <absl/strings/str_join.h>
#include <algorithm>
#include <qpp/qpp.h>
#include <string>
#include <vector>

namespace quafu {

class Gates {

public:
  Gates() {}
  Gates(const std::string &name, const std::vector<int> &positions,
        const std::vector<double> &params = {})
      : name(name), positions(positions), params(params) {}

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
  std::vector<int> positions{};
  std::vector<double> params{};
};

const std::string Gates::to_qasm() const {
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
  for (const auto &p : this->positions) {
    str_vec.push_back("q[" + absl::StrCat(p) + "]");
  }
  qasm_str += absl::StrJoin(str_vec, ",");
  return qasm_str;
}

} // namespace quafu
