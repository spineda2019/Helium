// Copyright 2024 Sebastian Pineda
#include <iostream>
#include <string>

#include "include/Lexer.hpp"

int main(int argc, char **argv) {
  std::string file_name{};

  switch (argc) {
  case 1:
    std::cerr << "FATAL: No input arguments given" << std::endl;
    return -1;
    break;
  case 2:
    file_name = argv[1];
    break;
  default:
    std::cerr << "FATAL: Please provide main.he" << std::endl;
    return -2;
    break;
  }

  int file_result = Lexer::ProcessFileName(file_name);
  if (file_result == -1) {
    std::cerr << "FATAL: File is not expected \"main.he\"" << std::endl;
    return -3;
  } else if (file_result == -2) {
    std::cerr << "FATAL: main.he does not exist" << std::endl;
    return -4;
  }

  auto lexed_tokens = Lexer::LexMainFile(file_name);
  if (!lexed_tokens.has_value()) {
    std::cerr << "FATAL: Unknown token classification found" << std::endl;
    return -1;
  } else {
    for (const auto &x : lexed_tokens.value()) {
      std::cout << x.GetIdentifier() << " ";
    }
  }

  return 0;
}
