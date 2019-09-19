#include "logger.hpp"

namespace new_logger
{

void Logger::printMessage(const std::string &msg, LogLevel lvl)
{
  auto prefix = std::string{};
  
  switch (lvl)
  {
  case LogLevel::LOW:
    prefix = "\033[1;33mAttention!\033[0m ";
    break;
  case LogLevel::MID:
    prefix = "\033[1;35mWarning!\033[0m ";
    break;
  case LogLevel::HIGH:
    prefix = "\033[1;31mError!\033[0m ";
    break;
  case LogLevel::DEBUG:
    prefix = "\033[1;36mDEBUG!\033[0m ";
    break;
  default:
    break;
  }

  std::lock_guard<std::mutex> lockGuardForCout(mut_cout_);
  std::cout << prefix << msg << std::endl;
}

void Logger::setFilename(const std::string &filename)
{
  sview_filename_ = filename;
}

}; // namespace new_logger

std::mutex Logger::mut_coutMutex_;

void Logger::printMessage(const std::string &msg, LogLevel lvl)
{
  std::lock_guard<std::mutex> lockGuardForCout(mut_coutMutex_);

  auto prefix = std::string{};
  switch (lvl)
  {
  case LogLevel::LOW:
    prefix = "\033[1;33mAttention!\033[0m ";
    break;
  case LogLevel::MID:
    prefix = "\033[1;35mWarning!\033[0m ";
    break;
  case LogLevel::HIGH:
    prefix = "\033[1;31mError!\033[0m ";
    break;
  case LogLevel::DEBUG:
    prefix = "\033[1;36mDEBUG!\033[0m ";
    break;
  default:
    break;
  }

  std::cout << prefix << msg << std::endl;
}
