/**
 * Copyright 2017 University of Southern California
 * Licensed under GPLv2 or any later version
 * Refer to the LICENSE file included.
 */
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <unistd.h>

std::shared_ptr<std::istream> GetInput(const char* inputFile){
    std::shared_ptr<std::istream> input;
    if (inputFile[0] == '-'){
        if (isatty(fileno(stdin))){
             std::cerr << "No support for terminal input.\n";
             exit(1);
        }
        std::ios_base::sync_with_stdio(false);
        input.reset(&std::cin, [](...){});
        
    }else
        input.reset(new std::ifstream(inputFile));
    
    return input;    
}

std::shared_ptr<std::ostream> GetOutput(const char* outputFile){
    std::shared_ptr<std::ostream> output;
    if (outputFile[0] == '-'){
        output.reset(&std::cout, [](...){});
    }else
        output.reset(new std::ofstream(outputFile));
    
    return output;    
}

std::vector<std::string> split(const std::string &text, char sep) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}
