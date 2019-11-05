#include "scene.h"
#include <string>
#include <iostream>

enum TokenType { Word, Number, LParen, RParen };

struct Token {
  TokenType type;
  std::string data;
};

class SceneParser {
    public:
  SceneParser(const std::string &src) : src(src), pos(0) {}
  Scene parse();
  private:
  std::string src;
  Scene s;
  unsigned int pos;

  std::vector<Token> tokenize();

  Token word() {
    auto start = pos;
    while (pos != src.length() && !isspace(src[pos])) {
      pos++;
    }
    return Token{TokenType::Word, src.substr(start, pos - start)};
  }
  Token num() {
    auto start = pos;
    if (src[start] == '-' || src[start] == '.') {
      pos++;
    }
    while (pos != src.length() && isdigit(src[pos])) {
      pos++;
    }
    return Token{TokenType::Number, src.substr(start, pos - start)};
  }
  Token scanToken() {
    while (isspace(src[pos])) {
      pos++;
    }
    if (isalpha(src[pos])) {
      return word();
    }
    if (isdigit(src[pos]) || src[pos] == '-' || src[pos] == '.') {
      return num();
    }
    if (src[pos] == '{') {
      pos++;
      return Token{TokenType::LParen, "{"};
    }
    if (src[pos] == '}') {
      pos++;
      return Token{TokenType::RParen, "}"};
    }
  }
};

std::vector<Token> SceneParser::tokenize() {
  std::vector<Token> tokens;
  while (pos != src.length()) {
    tokens.push_back(scanToken());
  }
  return tokens;
}

Scene SceneParser::parse() {
  auto tokens = tokenize();
  return s;
}

int main() {
   auto test = "Sphere {0 100 -1 20} Light {20 .30 40}" ;
   SceneParser sp(test);
   sp.parse();
}