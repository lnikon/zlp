#ifndef CODE_SECTION_PARSER_H
#define CODE_SECTION_PARSER_H

#include "parser_defs.hpp"
#include "logger.hpp"

#include <optional>
#include <fstream>

struct CodeSectionParser final
{
    explicit CodeSectionParser(logger::LoggerSPtr pLogger);
    ~CodeSectionParser() = default;

    CodeSectionParser(const CodeSectionParser &) = delete;
    CodeSectionParser &operator=(const CodeSectionParser &) = delete;

    CodeSectionParser(CodeSectionParser &&) = delete;
    CodeSectionParser &operator=(CodeSectionParser &&) = delete;

    CodeSection parse(std::fstream &inputStream);

    void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
    int getLineNumber() const { return lineNumber_; }

private:
    /*
    * Synchronized logger
    */
    logger::LoggerSPtr ps_logger_{nullptr};

    /*
     * Current line number in source file
     */
    int lineNumber_{0};

    /*
     * Number of functions
     */
    int functionCount_{0};

    /*
     * Simple symbol table for functions
     */
    SimpleSymbolTable functionTable_{};

    /*
     * Methods
     */
    std::optional<std::string>          getFunctionName(const std::string &line);
    std::optional<std::string>          isFunctionDeclaration(const std::string &line);
    void								parseFunctionBody(std::fstream &inputStream, Function &rFunc);
    std::optional<Label>				isLabel(const std::string &line);
    bool								endOfFunctionDecl(const std::string &line);
};

#endif // CODE_SECTION_PARSER_H
