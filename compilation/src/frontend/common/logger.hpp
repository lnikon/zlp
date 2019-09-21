#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <mutex>
#include <memory>

namespace logger
{

enum class LogLevel
{
  LOW = 0,
  MID,
  HIGH,
  DEBUG,
  INFO
};

std::string logLevelString(LogLevel lvl);

struct Printer final
{
  Printer() = default;
  ~Printer() = default;

  Printer(const Printer &) = delete;
  Printer &operator=(const Printer &) = delete;

  Printer(Printer &&) = delete;
  Printer &operator=(Printer &&) = delete;

  /*
  * Synchronizes @std::cout
  */
  void print(const std::string &prefix, const std::string &msg, const std::string &suffix);

private:
  std::mutex mut_cout_;
};
using PrinterSPtr = std::shared_ptr<Printer>;

struct Logger final
{
  Logger(PrinterSPtr pPrinter, const std::string &filename);
  ~Logger() = default;

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

  void setFilename(const std::string &filename);
  void printMessage(const std::string &msg, LogLevel lvl = LogLevel::LOW);

private:
  PrinterSPtr sh_printer_{nullptr};
  std::string_view sview_filename_;
};

using LoggerUPtr = std::unique_ptr<Logger>;
using LoggerSPtr = std::shared_ptr<Logger>;
using LoggerWPtr = std::weak_ptr<Logger>;

}; // namespace logger

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
