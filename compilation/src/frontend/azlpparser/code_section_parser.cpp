#include "code_section_parser.hpp"
#include "utility.hpp"
#include "logger.hpp"
#include "lexer_defs.hpp"

CodeSection CodeSectionParser::parse(std::fstream &inputStream)
{
  CodeSection codeSec;

  bool isCodeSectionPresent   = false;
  bool isCodeSectionOk        = false;
  auto line = std::string{};

  while(!isCodeSectionPresent && std::getline(inputStream, line))
  {
    lineNumber_++;

    line = utility::trim_copy(line);

    if(line.empty())
    {
      continue;
    }

    // If section .DATA doesn't present,
    // then start processing of the .CODE section
    // else, read the next line
    const auto codeSectionPos = line.find(CODE_SEC_NAME);
    isCodeSectionPresent = (codeSectionPos != std::string::npos);
  }

  if(!isCodeSectionPresent)
  {
    Logger::printMessage("Syntax error on line "
        + std::to_string(lineNumber_)
        + ". CODE section should contain at least one function for the main.\n", LogLevel::HIGH);
    exit(1);
  }

  while(!isCodeSectionOk && std::getline(inputStream, line))
  {
    lineNumber_++;

    line = utility::trim_copy(line);

    if(line.empty() || utility::starts_with(line, "#"))
    {
      continue;
    }

    const bool isMainSection = utility::starts_with(line, MAIN_SEC_NAME);
    if(isMainSection)
    {
      break;
    }

    auto name = getFunctionName(line);
    // TODO: Check for function name redifinition.
    Function func;

    parseFunctionBody(inputStream, func);
  }

  return codeSec;
}

std::pair<bool, std::string> CodeSectionParser::getFunctionName(const std::string& line)
{
    auto [isFuncDecl, funcName] = isFunctionDeclaration(line);
    if(!isFuncDecl && functionCount_ < 1)
    {
        Logger::printMessage("Syntax error on line "
                + std::to_string(lineNumber_)
                + ". Function declaration parsing failed.\n", LogLevel::HIGH);
        exit(1);
    }

    return std::make_pair(isFuncDecl, funcName);
}

std::pair<bool, std::string> CodeSectionParser::isFunctionDeclaration(const std::string& line)
{
    bool startWithFunctionKeyword = utility::starts_with(line, FUNCTION_KWRD);
    if(!startWithFunctionKeyword)
    {
        Logger::printMessage("Syntax error on line "
                + std::to_string(lineNumber_)
                + ". CODE section should start with function declaration.\n", LogLevel::HIGH);
        exit(1);
    }

    std::vector<std::string> tokens;
    utility::tokenize(line, tokens);
    for(auto& token : tokens)
    {
        token = utility::trim_copy(token);
    }

    if(tokens.size() > 3)
    {
        Logger::printMessage("Syntax error on line "
                + std::to_string(lineNumber_)
                + ". Too many tokens in function declaration.\n", LogLevel::HIGH);
        exit(1);
    }

    if(tokens.size() < 2)
    {
        Logger::printMessage("Syntax error on line "
                + std::to_string(lineNumber_)
                + ". Missing function name.\n", LogLevel::HIGH);
        exit(1);
    }

    auto funcName = tokens[1];
    funcName = utility::trim_copy(funcName);

    if(funcName[funcName.size() - 1] == ':')
    {
       funcName = funcName.substr(0, funcName.size() - 1);
    }

    if(!utility::checkCorrectKeyword(funcName))
    {

        Logger::printMessage("Syntax error on line "
                + std::to_string(lineNumber_)
                + ". Missing function name.\n", LogLevel::HIGH);
        exit(1);

    }

    const bool isFuncDecl = startWithFunctionKeyword && ((tokens.size() == 2) || (tokens.size() == 3));
    if(isFuncDecl)
    {
        functionCount_++;
    }

    return std::make_pair(isFuncDecl, funcName);
}

void CodeSectionParser::parseFunctionBody(std::fstream& inputStream, Function& rFunc)
{
    auto line = std::string{};
    while(std::getline(inputStream, line))
    {
        lineNumber_++;

        line = utility::trim_copy(line);

        if(line.empty() || utility::starts_with(line, "#"))
        {
            continue;
        }

        if(auto [isLabelParam, label] = isLabel(line); isLabelParam)
        {
            std::cout << "isLabelParam: " << isLabelParam << std::endl;
            std::cout << "lbl.name_: " << label.name_ << std::endl;

            rFunc.labels_.push_back(label);
        }
        else if(auto [isInstrParam, instr] = isInstruction(line); isInstrParam)
        {
            std::cout << "inInstrParam: " << isInstrParam << std::endl;
            std::cout << "instr.name_: " << instr.name_ << std::endl;

            rFunc.code_.push_back(instr);
        }
        else if(endOfFunctionDecl(line))
        {
            break;
        }
        else
        {
            Logger::printMessage("Syntax error on line "
                    + std::to_string(lineNumber_)
                    + ". Invalid statemant at function definition.\n", LogLevel::HIGH);
            exit(1);
        }
    }
}

std::pair<bool, Label> CodeSectionParser::isLabel(const std::string& line)
{
    auto label = Label{};
    auto isLabelParam = false;

    auto tokens = std::vector<std::string>{};
    utility::tokenize(line, tokens);

    // Label declaration can consist of maximum 2 tokens
    if(tokens.size() > 2)
    {
        isLabelParam = false;
        return std::make_pair(isLabelParam, label);
    }

    auto name = std::string{};
    if(tokens.size() == 2)
    {
        name = tokens[0];
        name = utility::trim_copy(name);

        isLabelParam = true;
    }
    else if(tokens.size() == 1)
    {
        name = tokens[0];
        name = utility::trim_copy(name);

        if(name[name.size() - 1] != ':')
        {
            isLabelParam = false;
            return std::make_pair(isLabelParam, label);
        }

        name = name.substr(0, name.size() - 1);

        if(!utility::checkCorrectKeyword(name))
        {
            Logger::printMessage("Syntax error on line "
                    + std::to_string(lineNumber_)
                    + ". Invalid identifier name for label.\n", LogLevel::HIGH);
            exit(1);

        }

        isLabelParam = true;
    }

    label.name_ = name;

    return std::make_pair(isLabelParam, label);
}

std::pair<bool, Instruction> CodeSectionParser::isInstruction(const std::string& line)
{
    bool isInstr = false;

    return std::make_pair(isInstr, Instruction{});
}


std::pair<bool, InstructionType> CodeSectionParser::isInstructionType(const std::string& token)
{

  return std::make_pair(false, InstructionType::NOP);
}

std::pair<bool, Extension> CodeSectionParser::isExtension(const std::string& token)
{
  return std::make_pair(false, Extension::DWORD);
}

std::pair<bool, OpList> CodeSectionParser::isOperandList(const std::string& token)
{
  return std::make_pair(false, OpList{});
}

bool CodeSectionParser::endOfFunctionDecl(const std::string& line)
{
  return !(line.compare(END_FUNCTION_KWRD));
}
