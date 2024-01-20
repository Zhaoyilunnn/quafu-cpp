#pragma once

#include "nlohmann/json.hpp"
#include "quafu/exceptions.hpp"

namespace quafu {

class Result {

public:
  Result(){};
  Result(const std::string &res) {
    // Check format
    nlohmann::json j;
    try {
      j = nlohmann::json::parse(res);
    } catch (std::exception) {
      throw ResultException("Result is not json format");
    }

    // Populate contents
    POPULATE_RESULT_FIELD(j, res, _counts);
    POPULATE_RESULT_FIELD(j, task_id, _task_id);

    // Calculate _probabilities
    // TODO()
  }

  // Attribute getters
  const std::string &task_id() { return _task_id; }
  const nlohmann::json &counts() { return _counts; }
  const nlohmann::json &probabilities() { return _probabilities; }

private:
  // Result attributes
  std::string _task_id;          // Task ID
  nlohmann::json _counts;        // Occurance of each measurement result
  nlohmann::json _probabilities; // Probabilities of each measurement result
};

} // namespace quafu
