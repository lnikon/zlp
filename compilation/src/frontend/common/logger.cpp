#include "logger.hpp"

void Logger::printMessage(const std::string& msg, LogLevel lvl)
{
  auto prefix = std::string{};
  switch(lvl)
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
