// Copyright 2024 Sebastian Pineda
#include <optional>
#include <string>

#include "include/Token.hpp"
namespace Lexer {

Token::Token(std::optional<std::string> identifier,
             std::optional<std::string> literal_value)
    : identifier_(identifier), literal_value_(literal_value) {}
// Debug Purposes only
std::string Token::GetIdentifier() const {
  return this->identifier_.value_or("NONE");
}
} // namespace Lexer
