// Copyright 2024 Sebastian Pineda
#ifndef SRC_INCLUDE_LEXER_HPP_
#define SRC_INCLUDE_LEXER_HPP_

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "Token.hpp"

namespace Lexer {

constexpr std::array<char, 6> valid_simple_operators{'+', '-', '/',
                                                     '*', '<', '>'};

enum class CharacterType : std::uint8_t {
  NumberLiteral,
  Decimal,
  NewLine,
  Whitespace,
  Operator,
  GroupingSymbol,
  SemiColon,
  Letter,
};

enum class LexemeType : std::uint8_t {
  SimpleOperator,
  CompoundOperator,
  LeftParenthesis,
  RightParenthesis,
  LeftBracket,
  RightBracket,
  IntegerLiteral,
  FloatLiteral,
  Identifier,
  Empty
};

const std::optional<CharacterType> ClassifyCharacter(const char &letter);

int ProcessFileName(const std::string &file_name);
std::optional<std::vector<Token>> LexMainFile(const std::string &file_name);
} // namespace Lexer

#endif // SRC_INCLUDE_LEXER_HPP_
