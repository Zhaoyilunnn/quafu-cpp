#include "quafu/result.hpp"
#include "gtest/gtest.h"

const nlohmann::json SAMPLE_RES = {
    {"measure", "{0: 0, 1: 1}"},
    {"openqasm",
     "OPENQASM 2.0;\ninclude \"qelib1.inc\";\nqreg q[2];\ncreg meas[2];\nh "
     "q[0];\nx q[1];\nmeasure q[0] -> meas[0];\nmeasure q[1] -> meas[1];\n"},
    {"raw", "{\"11\": 505, \"01\": 475, \"10\": 13, \"00\": 7}"},
    {"res", "{\"11\": 505, \"01\": 475, \"10\": 13, \"00\": 7}"},
    {"status", 2},
    {"task_id", "3DC841902FE36E0F"},
    {"task_name", ""}};

const nlohmann::json SAMPLE_RES_ABNORMAL = {
    {"measure", "{0: 0, 1: 1}"},
    {"res", "{\"11\": 505, \"01\": 475, \"10\": 13, \"00\": 7}"},
    {"status", 2},
    {"task_name", ""}};

TEST(ResultTest, construction) {
  // Normal result
  auto j_str = SAMPLE_RES.dump();
  auto r = quafu::Result(j_str);
  ASSERT_EQ(r.task_id(), "3DC841902FE36E0F");
  ASSERT_EQ(r.counts(), "{\"11\": 505, \"01\": 475, \"10\": 13, \"00\": 7}");

  // Abnormal result: missing fields
  auto j_str_abnormal = SAMPLE_RES_ABNORMAL.dump();
  ASSERT_THROW(r = quafu::Result(j_str_abnormal), quafu::ResultException);

  // Abnormal result: non-json format
  ASSERT_THROW(r = quafu::Result("some non json format"),
               quafu::ResultException);
}
