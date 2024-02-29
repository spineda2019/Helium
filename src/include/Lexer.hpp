// Copyright 2024 Sebastian Pineda
#ifndef SRC_INCLUDE_LEXER_HPP_
#define SRC_INCLUDE_LEXER_HPP_

#include <string>
#include <vector>

#include "Token.hpp"

namespace Lexer {
int ProcessFileName(const std::string &file_name);
std::vector<Token> LexMainFile(const std::string &file_name);
} // namespace Lexer

#endif // SRC_INCLUDE_LEXER_HPP_
