#pragma once

#include "compilation_pipeline.hpp"
#include "logger.hpp"

#include <vector>
#include <thread>

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
  std::vector<std::thread>  vec_pipelines_{};
  std::vector<std::string>  svec_inputFilenames_{};

  logger::PrinterSPtr ps_printer_{nullptr};
  logger::LoggerSPtr ps_logger_{nullptr};
};