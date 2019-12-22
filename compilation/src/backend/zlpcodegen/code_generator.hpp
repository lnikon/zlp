#pragma once

#include "compilation_pipeline.hpp"
#include "logger.hpp"

#include <vector>
#include <thread>
#include <future>

template <class FirstValueType, class SecondValueType>
std::vector<std::pair<FirstValueType, SecondValueType>>
zip(const std::vector<FirstValueType>& first, const std::vector<SecondValueType>& second)
{
    std::vector<std::pair<FirstValueType, SecondValueType>> result{};

    const auto size = first.size();
    for(auto i = 0u; i < size; ++i)
    {
        result.emplace_back(std::make_pair(first[i], second[i]));
    }

    return result;
}

struct CodeGenerator {
    CodeGenerator();

    CodeGenerator(const CodeGenerator&) = delete;
    CodeGenerator& operator=(const CodeGenerator&) = delete;

    CodeGenerator(CodeGenerator&&) = delete;
    CodeGenerator& operator=(CodeGenerator&&) = delete;

    /*
  * Actual stuff for compilation.
  * Consider to return/output 'compilation units'.
  */
    void build();

    /*
   * Setters for filename vectors
   */
    void setInputFilenames(std::vector<std::string> &&inputFilenames);
    void setInputFilenames(const std::vector<std::string> &inputFilenames);

private:
    ns_compilation_unit::SPtrCompilationUnitPromiseVec ps_vec_compUnitsPromises_;
    ns_compilation_unit::SPtrCompilationUnitFutureVec  ps_vec_compUnitsFutures_;

    std::vector<std::string>  svec_inputFilenames_{};

    logger::PrinterSPtr ps_printer_{nullptr};
    logger::LoggerSPtr  ps_logger_{nullptr};
};
