// Copyright 2024 Sebastian Pineda
#include <filesystem>
#include <string>
#include <vector>

#include "Lexer.hpp"
#include "Token.hpp"

namespace Lexer {
int ProcessFileName(const std::string &file_name) {
  if (file_name != "main.he") {
    return -1;
  } else if (!std::filesystem::exists(file_name)) {
    return -2;
  } else {
    return 0;
  }
}

std::vector<Token> LexMainFile(const std::string &file_name) {
  std::vector<Token> tokens{};

  return std::move(tokens);
}
} // namespace Lexer
