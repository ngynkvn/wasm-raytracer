#include "defs.h"
#include <deque>
#include <iostream>
#include <string>

enum TokenType { Word, Number, LParen, RParen, EndOfFile };

struct Token {
  TokenType type;
  std::string datum;
};

class SceneParser {
public:
  SceneParser(const std::string &src) : src(src), pos(0) {}
  Scene parse();

private:
  std::string src;
  Scene scene;
  unsigned int pos;

  std::deque<Token> tokens;
  void tokenize();

  Token word();
  Token number();
  void scanToken();
  
  Sphere constructSphere();
  Light constructLight();
  Point constructCamera();
  Color constructColor();
  Point constructPoint();
  Token consume(TokenType);
};