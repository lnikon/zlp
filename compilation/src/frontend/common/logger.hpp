#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <mutex>
#include <memory>

namespace new_logger
{

enum class LogLevel
{
  LOW = 0,
  MID,
  HIGH,
  DEBUG,
};

struct Logger final
{
  Logger() = default;
  ~Logger() = default;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

  void setFilename(const std::string& filename);
  void printMessage(const std::string &msg, LogLevel lvl = LogLevel::LOW);

  private:
  std::mutex mut_cout_;
  std::string_view sview_filename_;
};

using LoggerUPtr = std::unique_ptr<Logger>;
using LoggerSPtr = std::shared_ptr<Logger>;
using LoggerWPtr = std::weak_ptr<Logger>;

}; // namespace new_logger

enum class LogLevel
{
  LOW = 0,
  MID,
  HIGH,
  DEBUG,
};

struct Logger final
{
  static void printMessage(const std::string &msg, LogLevel lvl = LogLevel::LOW);
  static std::mutex mut_coutMutex_;
};
