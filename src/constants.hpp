#pragma once

#include <cstdlib>
#include <string>

// Quafu cloud platform APIs
const std::string API_BACKENDS = "qbackend/get_backends/";
const std::string API_CHIP = "qbackend/scq_get_chip_info/";
const std::string API_EXEC = "qbackend/scq_kit/";
const std::string API_EXEC_ASYNC = "qbackend/scq_kit_asyc/";
const std::string API_EXEC_RECALL = "qbackend/scq_task_recall/";

// Misc
// TODO(zhaoyilun): depends on OS
const std::string HOME = std::getenv("HOME");
const std::string CRED_PATH = HOME + "/.quafu/api";
