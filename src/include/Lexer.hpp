// Copyright 2024 Sebastian Pineda
#ifndef SRC_INCLUDE_LEXER_HPP_
#define SRC_INCLUDE_LEXER_HPP_

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "Token.hpp"

namespace Lexer {

constexpr std::array<char, 7> valid_simple_operators{'+', '-', '/', '*',
                                                     '<', '>', '='};

constexpr std::array<std::string_view, 7> valid_operators{"+", "-", "/", "*",
                                                          "<", ">", "="};

constexpr std::array<std::string_view, 5> valid_compound_operators{
    "->", "+=", "-=", "*=", "/="};

constexpr std::array<std::string_view, 1> valid_comment_starters{"//"};

constexpr std::array<std::string_view, 10> primitive_types{
    "sint8",   "sint16", "sint32", "sint64", "float32",
    "float64", "uint8",  "uint16", "uint32", "uint64",
};

enum class CharacterType : std::uint8_t {
  PartOfType,
  NumberLiteral,
  Decimal,
  NewLine,
  Whitespace,
  Operator,
  GroupingSymbol,
  LeftScopeDelimiter,
  RightScopeDelimiter,
  SemiColon,
  CommentLetter,
  Letter,
};

enum class LexemeType : std::uint8_t {
  SimpleOperator,
  CompoundOperator,
  LeftParenthesis,
  RightParenthesis,
  LeftBracket,
  RightBracket,
  LeftBrace,
  RightBrace,
  PrimitiveType,
  IntegerLiteral,
  FloatLiteral,
  Identifier,
  CommentStart,
  CommentWord,
  Whitespace,
};

const std::optional<LexemeType> ClassifyLexeme(const std::string_view lexeme);

const std::optional<CharacterType>
ClassifyCharacter(const char &letter, const std::string_view incomplete_lexeme);

const bool IsLexemeEmpty(const std::string_view lexeme);

int ProcessFileName(const std::string &file_name);
std::optional<std::vector<Token>> LexMainFile(const std::string &file_name);

} // namespace Lexer

#endif // SRC_INCLUDE_LEXER_HPP_
