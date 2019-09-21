#include "stack_section_parser_utilities.hpp"

#include "logger.hpp"
#include "vm_config.hpp"

bool StackSectionParserUtilities::checkStackSection(const StackSection& stackSec, logger::LoggerSPtr pLogger)
{
  bool isAllOk = true;

  // Check stack size
  const std::size_t stackSize = stackSec.size_;
  const bool stackSizeOk = checkStackSize(stackSize, pLogger);

  if(!stackSizeOk)
  {
    pLogger->printMessage("Incorrect stack size: " + std::to_string(stackSize), logger::LogLevel::HIGH);
  }

  isAllOk = stackSizeOk;  // && with other check flags
  return isAllOk;
}

bool StackSectionParserUtilities::checkStackSize(const std::size_t stackSize, logger::LoggerSPtr)
{
  return (stackSize < VM_MAX_STACK_SIZE);
}
