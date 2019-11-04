#include "code_section_parser.hpp"
#include "instruction_parser.hpp"
#include "lexer_defs.hpp"
#include "utility.hpp"

CodeSectionParser::CodeSectionParser(logger::LoggerSPtr pLogger)
    : ps_logger_{pLogger}
{
}

CodeSection CodeSectionParser::parse(std::fstream &inputStream)
{
    CodeSection codeSec;

    bool isCodeSectionPresent = false;
    bool isCodeSectionOk = false;
    auto line = std::string{};

    while (!isCodeSectionPresent && std::getline(inputStream, line))
    {
        line = utility::trim_copy(line);

        if (line.empty())
        {
            continue;
        }

        // If section .DATA doesn't present,
        // then start processing of the .CODE section
        // else, read the next line
        const auto codeSectionPos = line.find(CODE_SEC_NAME);
        isCodeSectionPresent = (codeSectionPos != std::string::npos);

        lineNumber_++;
    }

    if (!isCodeSectionPresent)
    {
        ps_logger_->printMessage("Syntax error on line " +
                                     std::to_string(lineNumber_) +
                                     ". CODE section should contain at least "
                                     "one function for the main",
                                 logger::LogLevel::HIGH);
        exit(1);
    }

    while (!isCodeSectionOk && std::getline(inputStream, line))
    {
        line = utility::trim_copy(line);

        if (line.empty() || utility::starts_with(line, "#"))
        {
            continue;
        }

        const bool isMainSection = utility::starts_with(line, MAIN_SEC_NAME);
        if (isMainSection)
        {
            break;
        }

        std::size_t funcIndex = 0;

        const auto &nameOpt = getFunctionName(line);
        if (nameOpt.has_value())
        {
            const auto &name = nameOpt.value();
            if (auto it = functionTable_.find(name);
                it != std::end(functionTable_))
            {
                funcIndex = it->second;
            }
            else
            {
                Function func;
                func.name_ = name;

                codeSec.code_.emplace_back(func);
                funcIndex = codeSec.code_.size() - 1;
                functionTable_.emplace(name, funcIndex);
            }
        }
        else
        {
            ps_logger_->printMessage("Error occured during function parsing\n",
                                     logger::LogLevel::HIGH);
            exit(1);
        }

        Function &func = codeSec.code_[funcIndex];
        parseFunctionBody(inputStream, func);

        // Insert parsed function into functions list
        //        codeSec.insertFunction(func);

        // Go to next line, at it isn't harmful :)
        lineNumber_++;
    }

    return codeSec;
}

std::optional<std::string>
CodeSectionParser::getFunctionName(const std::string &line)
{
    auto funcName = isFunctionDeclaration(line);
    return funcName;
}

std::optional<std::string>
CodeSectionParser::isFunctionDeclaration(const std::string &line)
{
    bool startWithFunctionKeyword = utility::starts_with(line, FUNCTION_KWRD);
    if (!startWithFunctionKeyword)
    {
        ps_logger_->printMessage(
            "Syntax error on line " + std::to_string(lineNumber_) +
                ". CODE section should start with function declaration",
            logger::LogLevel::HIGH);
        return std::nullopt;
    }

    std::vector<std::string> tokens;
    utility::tokenize(line, tokens);
    for (auto &token : tokens)
    {
        token = utility::trim_copy(token);
    }

    if (tokens.size() > 3)
    {
        ps_logger_->printMessage(
            "Syntax error on line " + std::to_string(lineNumber_) +
                ". Too many tokens in function declaration.\n",
            logger::LogLevel::HIGH);
        return std::nullopt;
    }

    if (tokens.size() < 2)
    {
        ps_logger_->printMessage("Syntax error on line " +
                                     std::to_string(lineNumber_) +
                                     ". Missing function name",
                                 logger::LogLevel::HIGH);
        return std::nullopt;
    }

    auto funcName = tokens[1];
    funcName = utility::trim_copy(funcName);

    if (funcName[funcName.size() - 1] == ':')
    {
        funcName = funcName.substr(0, funcName.size() - 1);
    }

    if (!utility::checkCorrectKeyword(funcName))
    {
        ps_logger_->printMessage("Syntax error on line " +
                                     std::to_string(lineNumber_) +
                                     ". Missing function name",
                                 logger::LogLevel::HIGH);
        return std::nullopt;
    }

    //    const bool isFuncDecl = startWithFunctionKeyword && ((tokens.size() ==
    //    2) || (tokens.size() == 3)); if (isFuncDecl)
    //    {
    //        functionCount_++;
    //    }

    return std::make_optional(funcName);
}

void CodeSectionParser::parseFunctionBody(std::fstream &inputStream,
                                          Function &rFunc)
{
    /*
     * Don't declare labelTabel as member of class because it's local to a
     * function
     */
    SimpleSymbolTable labelTabel;
    SimpleSymbolTable DUMMY_DATA_TABLE;

    InstructionParser instrParser{ps_logger_, DUMMY_DATA_TABLE, functionTable_,
                                  labelTabel};

    /*
     *  Remember current position of fstream
     */
    const auto originalCursor = inputStream.tellg();

    /*
     *  Do preprocessing of labels
     */
    auto line = std::string{};
    while (std::getline(inputStream, line))
    {
        if (auto label = isLabel(line); label.has_value())
        {
            rFunc.labels_.emplace_back(label.value());

            const auto labelIndex = rFunc.labels_.size() - 1;
            labelTabel.emplace(label.value().name_, labelIndex);
        }
    }

    line.clear();
    inputStream.seekg(originalCursor);
    while (std::getline(inputStream, line))
    {
        lineNumber_++;
        instrParser.lineNumber_ = lineNumber_;

        line = utility::trim_copy(line);

        if (line.empty() || utility::starts_with(line, "#"))
        {
            continue;
        }

        //        if (auto label = isLabel(line); label.has_value())
        //        {
        //            rFunc.labels_.emplace_back(label.value());
        //        }
        /*else */ if (auto instruction = instrParser.parse(line);
                      instruction.has_value())
        {
            rFunc.code_.emplace_back(instruction.value());
        }
        else if (endOfFunctionDecl(line))
        {
            break;
        }
        else
        {
            ps_logger_->printMessage(
                "Syntax error on line " + std::to_string(lineNumber_) +
                    ". Invalid statemant at function definition.\n",
                logger::LogLevel::HIGH);
            exit(1);
        }
    }
}

std::optional<Label> CodeSectionParser::isLabel(const std::string &line)
{
    auto label = Label{};
    auto isLabelParam = false;

    auto tokens = std::vector<std::string>{};
    utility::tokenize(line, tokens);

    /*
     * Label declaration can consist of maximum 2 tokens
     */
    if (tokens.size() > 2)
    {
        return std::nullopt;
    }

    auto name = std::string{};
    if (tokens.size() == 2)
    {
        name = tokens[0];
        name = utility::trim_copy(name);
    }
    else if (tokens.size() == 1)
    {
        name = tokens[0];
        name = utility::trim_copy(name);

        if (name[name.size() - 1] != ':')
        {
            return std::nullopt;
        }

        name = name.substr(0, name.size() - 1);

        if (!utility::checkCorrectKeyword(name))
        {
            ps_logger_->printMessage("Syntax error on line " +
                                         std::to_string(lineNumber_) +
                                         ". Invalid identifier name for label",
                                     logger::LogLevel::HIGH);
            exit(1);
        }
    }

    label.name_ = name;

    return label;
}

bool CodeSectionParser::endOfFunctionDecl(const std::string &line)
{
    return !(line.compare(END_FUNCTION_KWRD));
}
