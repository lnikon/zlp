#include "stack_section_parser.hpp"

#include "utility.hpp"
#include "lexer_defs.hpp"
#include "logger.hpp"
#include "vm_config.hpp"
#include "debug.hpp"

StackSectionParser::StackSectionParser(logger::LoggerSPtr pLogger)
    : ps_logger_{pLogger}
{
}

StackSection StackSectionParser::parse(std::fstream &inputStream)
{
    StackSection stackSec;

    bool isStackSizeOk = false;
    auto line = std::string{};

    while (!isStackSizeOk && std::getline(inputStream, line))
    {
        lineNumber_++;

        line = utility::trim_copy(line);

        if (line.empty() || utility::starts_with(line, "#"))
        {
            continue;
        }

        isStackSizeOk = parseStackSize(stackSec, line);

        if (!isStackSizeOk)
        {
            lineNumber_--;
            break;
        }
    }

    // If stack size hasn't been specified,
    // then set it to the default value
    if (!isStackSizeOk)
    {
        setDefaultStackSize(stackSec);
    }

    // Some debugging :)
    debug::print(stackSec, ps_logger_);

    return stackSec;
}

bool StackSectionParser::parseStackSize(StackSection &rStackSec, std::string line)
{
    bool isStackSizeOk = false;

    const std::size_t posOfStack = line.find(STACK_SEC_NAME);
    if (posOfStack != std::string::npos)
    {
        // Check assignment sign
        const std::size_t assignPos = line.find("=");
        if (assignPos == std::string::npos)
        {
            ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing assignment sign\n", logger::LogLevel::HIGH);

            isStackSizeOk = false;
            exit(1);
        }

        // Parse value of the stack size
        const auto stackSizeValueStr = utility::trim_copy(line.substr(assignPos + 1, line.size() - assignPos));
        if (stackSizeValueStr.empty())
        {
            ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing stack size value\n", logger::LogLevel::HIGH);

            isStackSizeOk = false;
            exit(1);
        }

        bool isStackSizeValueCorrectNumber = utility::is_number(stackSizeValueStr);
        if (!isStackSizeValueCorrectNumber)
        {
            ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Stack size value should be non-negative integer\n", logger::LogLevel::HIGH);
            isStackSizeOk = false;
            exit(1);
        }

        const auto stackSizeValueNum = std::stol(stackSizeValueStr);
        isStackSizeOk = true;
        rStackSec.size_ = stackSizeValueNum;
    }

    return isStackSizeOk;
}

void StackSectionParser::setDefaultStackSize(StackSection &rStackSec)
{
    ps_logger_->printMessage("Value for stack size didn\'t specified. Defaulting to " +
                                 std::to_string(VM_DEFAULT_STACK_SIZE) +
                                 ".\n",
                             logger::LogLevel::MID);

    rStackSec.size_ = VM_DEFAULT_STACK_SIZE;
}
