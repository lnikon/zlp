#include "logger.hpp"

namespace logger
{

void Printer::print(const std::string &prefix, const std::string &msg, const std::string &suffix)
{
  std::lock_guard coutMutexGuard(mut_cout_);
  std::cout << prefix << msg << suffix << std::endl;
}

Logger::Logger(PrinterSPtr pPrinter, const std::string &filename)
    : sh_printer_{pPrinter},
      sview_filename_{filename}
{
}

void Logger::printMessage(const std::string &msg, LogLevel lvl)
{
  /*
  * Prefix to be attached to the message
  */
  auto prefix = std::string{};

  /*
  * Prepend log level string
  */
  prefix += logLevelString(lvl);

  /*
  * Add filename after
  */
  prefix += sview_filename_;
  prefix += ": ";

  /*
  * Print the message via shared printer which synchronizes @std::cout with other @Logger class instances
  */
  sh_printer_->print(prefix, msg, "");
}

void Logger::setFilename(const std::string &filename)
{
  sview_filename_ = filename;
}

std::string logLevelString(LogLevel lvl)
{
  auto lvlString = std::string{};
  switch (lvl)
  {
  case LogLevel::LOW:
    lvlString = "\033[1;33mAttention!\033[0m ";
    break;
  case LogLevel::MID:
    lvlString = "\033[1;35mWarning!!\033[0m ";
    break;
  case LogLevel::HIGH:
    lvlString = "\033[1;31mError!!!\033[0m ";
    break;
  case LogLevel::DEBUG:
    lvlString = "\033[1;36mDEBUG!\033[0m ";
    break;
  case LogLevel::INFO:
    lvlString = "\033[1;32mInformation!\033[0m ";
  default:
    break;
  }

  return lvlString;
}

}; // namespace logger

std::mutex Logger::mut_coutMutex_;

void Logger::printMessage(const std::string &msg, LogLevel lvl)
{
  // std::lock_guard<std::mutex> lockGuardForCout(mut_coutMutex_);

  // auto prefix = std::string{};
  // switch (lvl)
  // {
  // case LogLevel::LOW:
  //   prefix = "\033[1;33mAttention!\033[0m ";
  //   break;
  // case LogLevel::MID:
  //   prefix = "\033[1;35mWarning!\033[0m ";
  //   break;
  // case LogLevel::HIGH:
  //   prefix = "\033[1;31mError!\033[0m ";
  //   break;
  // case LogLevel::DEBUG:
  //   prefix = "\033[1;36mDEBUG!\033[0m ";
  //   break;
  // default:
  //   break;
  // }

  // std::cout << prefix << msg << std::endl;
}
