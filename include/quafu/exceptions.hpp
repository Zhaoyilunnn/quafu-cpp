#pragma once

#include <stdexcept>

namespace quafu {

class Exception : public std::exception {

protected:
  std::string _msg;

public:
  Exception(const std::string &msg) : _msg(msg) {}

  const char *what() const noexcept override { return _msg.c_str(); }
};

class BackendException : public Exception {
public:
  BackendException(const std::string &msg) : Exception(msg) {}
};

#define CHECK_WEBSITE_ERROR(return_code)                                       \
  if (return_code >= 500) {                                                    \
    throw BackendException("Something wrong with Quafu website, please "       \
                           "contact quafu-support@baqis.ac.cn");               \
  }

} // namespace quafu
