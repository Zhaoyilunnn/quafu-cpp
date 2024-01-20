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

class ResultException : public Exception {
public:
  ResultException(const std::string &msg) : Exception(msg) {}
};

#define CHECK_WEBSITE_ERROR(return_code)                                       \
  if (return_code >= 500) {                                                    \
    throw BackendException("Something wrong with Quafu website, please "       \
                           "contact quafu-support@baqis.ac.cn");               \
  }

#define POPULATE_RESULT_FIELD(res, src, dest)                                  \
  if (res.contains(#src)) {                                                    \
    dest = res[#src];                                                          \
  } else {                                                                     \
    throw ResultException(                                                     \
        #src +                                                                 \
        std::string(                                                           \
            " missing in result, please contact quafu-support@baqis.ac.cn"));  \
  }

} // namespace quafu
