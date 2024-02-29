// Copyright 2024 Sebastian Pineda
#ifndef SRC_INCLUDE_LEXER_HPP_
#define SRC_INCLUDE_LEXER_HPP_

#include "Token.hpp"
#include <vector>
namespace Lexer {
std::vector<Token> &&LexMainFile();
} // namespace Lexer

#endif // SRC_INCLUDE_LEXER_HPP_
