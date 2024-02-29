// Copyright 2024 Sebastian Pineda
#ifndef SRC_INCLUDE_TOKEN_HPP_
#define SRC_INCLUDE_TOKEN_HPP_
#include <optional>
#include <string>
namespace Lexer {
class Token {
public:
  Token(std::optional<std::string> identifier,
        std::optional<std::string> literal_value);

private:
  std::optional<std::string> identifier_;
  std::optional<std::string> literal_value_;
}; // class Token
} // namespace Lexer
#endif // SRC_INCLUDE_TOKEN_HPP_
