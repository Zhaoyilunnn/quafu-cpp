#pragma once

#include <stdexcept>

namespace quafu {

class Exception : public std::exception {

private:
  std::string _msg = "QUAFU_ERROR!";

public:
  Exception(const std::string &msg) : _msg(msg) {}

  const char *what() const noexcept override { return _msg.c_str(); }
};

class BackendException : public Exception {};

} // namespace quafu
