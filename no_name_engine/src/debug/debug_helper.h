#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <unordered_map>

namespace nn {
static class DebugHelper {
public:
  static void NLog_info(const std::string &message) { spdlog::info(message); }

  static void NLog_error(const std::string &message) { spdlog::error(message); }

  static void NLog_warn(const std::string &message) { spdlog::warn(message); }
};
} // namespace NNEngine
