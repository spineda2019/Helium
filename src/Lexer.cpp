// Copyright 2024 Sebastian Pineda
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "include/Lexer.hpp"
#include "include/Token.hpp"

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

const std::optional<CharacterType> ClassifyCharacter(const char &letter) {
  //
  if (std::isdigit(letter)) {
    return CharacterType::NumberLiteral;
  } else if (letter == '.') {
    return CharacterType::Decimal;
  } else if (letter == '\n') {
    return CharacterType::NewLine;
  } else if (std::isspace(letter)) {
    return CharacterType::Whitespace;
  } else if (std::find(valid_simple_operators.begin(),
                       valid_simple_operators.end(),
                       letter) != valid_simple_operators.end()) {
    return CharacterType::Operator;
  } else if (letter == '(' || letter == ')') {
    return CharacterType::GroupingSymbol;
  } else if (letter == ';') {
    return CharacterType::SemiColon;
  } else if (std::isalpha(letter)) {
    return CharacterType::Letter;
  } else {
    return {};
  }
}

std::optional<std::vector<Token>> LexMainFile(const std::string &file_name) {
  std::vector<Token> tokens{};
  std::ifstream main_file(file_name);

  char current_character{};
  std::string built_lexeme{};
  std::optional<CharacterType> current_character_type(
      CharacterType::Whitespace);
  LexemeType current_lexeme_type(LexemeType::Empty);

  while (main_file.get(current_character)) {
    std::cout << "found a char: " << current_character << std::endl;
    current_character_type = ClassifyCharacter(current_character);
    if (!current_character_type.has_value()) {
      // Terminate Compilation
      return {};
    }
  }

  return std::move(tokens);
}
} // namespace Lexer
