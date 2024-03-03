// Copyright 2024 Sebastian Pineda
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
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

const std::optional<LexemeType> ClassifyLexeme(const std::string_view lexeme) {
  if (lexeme == "(") {
    return LexemeType::LeftParenthesis;
  } else if (lexeme == ")") {
    return LexemeType::RightParenthesis;
  } else if (lexeme == "[") {
    return LexemeType::LeftBracket;
  } else if (lexeme == "]") {
    return LexemeType::RightBracket;
  } else if (std::find(valid_operators.begin(), valid_operators.end(),
                       lexeme) != valid_operators.end()) {
    return LexemeType::SimpleOperator;
  } else if (std::find(valid_compound_operators.begin(),
                       valid_compound_operators.end(),
                       lexeme) != valid_compound_operators.end()) {
    return LexemeType::CompoundOperator;
  } else if (std::find(valid_comment_starters.begin(),
                       valid_comment_starters.end(),
                       lexeme) != valid_comment_starters.end()) {
    return LexemeType::CommentStart;
  } else if (lexeme.find_last_not_of(' ') == std::string::npos) {
    return LexemeType::Whitespace;
  } else {
    return LexemeType::Identifier;
    // FOR NOW, TODO(sep) bring back return {};
  }
}

const std::optional<CharacterType> ClassifyCharacter(const char &letter) {
  std::cout << "Classify function found char: " << letter
            << " ASCII: " << static_cast<int>(letter) << std::endl;
  if (std::isdigit(letter)) {
    return CharacterType::NumberLiteral;
  } else if (letter == '.') {
    return CharacterType::Decimal;
  } else if (letter == '\n') {
    return CharacterType::NewLine;
  } else if (std::isspace(letter) || letter == ' ') {
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
  bool comment_found(false);

  std::optional<CharacterType> previous_character_type{};
  std::optional<CharacterType> current_character_type(
      CharacterType::Whitespace);
  std::optional<LexemeType> current_lexeme_type{};

  while (main_file.get(current_character)) {
    std::cout << "found a char: " << current_character
              << "ASCII: " << static_cast<int>(current_character) << std::endl;
    current_character_type = ClassifyCharacter(current_character);
    if (!current_character_type.has_value()) {
      // Terminate Compilation
      if (!comment_found) {
        return {};
      } else {
        continue;
      }
    }

    if (current_character_type == CharacterType::NewLine) {
      comment_found = false;
    }

    // determine if lexeme is done
    if (!previous_character_type.has_value()) {
      // TODO(sep): not done, special case of first character
      built_lexeme.push_back(std::move(current_character));
      previous_character_type = std::move(current_character_type);
      continue;
    }

    if (current_character_type.value() == previous_character_type.value()) {
      // still not done
      built_lexeme.push_back(std::move(current_character));
    } else {
      // finally done
      current_lexeme_type = ClassifyLexeme(built_lexeme);
      if (!current_lexeme_type.has_value()) {
        return {};
      }
      switch (current_lexeme_type.value()) {
      case LexemeType::Whitespace:
      case LexemeType::SimpleOperator:
      case LexemeType::CompoundOperator:
      case LexemeType::LeftParenthesis:
      case LexemeType::RightParenthesis:
      case LexemeType::LeftBracket:
      case LexemeType::RightBracket:
        tokens.emplace_back(built_lexeme, std::optional<std::string>{});
        break;
      case LexemeType::CommentStart:
        comment_found = true;
        tokens.emplace_back(built_lexeme, std::optional<std::string>{});
      case LexemeType::IntegerLiteral:
        // TODO(sep)
        tokens.emplace_back(built_lexeme, built_lexeme);
        break;
      case LexemeType::FloatLiteral:
        // TODO(sep)
        tokens.emplace_back(built_lexeme, built_lexeme);
        break;
      case LexemeType::Identifier:
        // TODO(sep)
        tokens.emplace_back(built_lexeme, std::optional<std::string>{});
        break;
      }
    }

    previous_character_type = std::move(current_character_type);
  }

  return std::move(tokens);
}
} // namespace Lexer
