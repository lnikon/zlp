#pragma once

#include "compilation_pipeline.hpp"

#include <vector>
#include <thread>

struct CodeGenerator {
  CodeGenerator() = default;
  
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
  // std::vector<CompilerSPtr> pCompilers_{};
  std::vector<std::thread>  pPipelines_{};
  std::vector<std::string>  inputFilenames_{};
};