#include "scene.h"
#include <deque>
#include <iostream>
#include <string>

enum TokenType { Word, Number, LParen, RParen };

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

  Token word() {
    auto start = pos;
    while (pos != src.length() && !isspace(src[pos]) && isalpha(src[pos])) {
      pos++;
    }
    return Token{TokenType::Word, src.substr(start, pos - start)};
  }
  Token number() {
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
    while (pos != src.length() && isspace(src[pos])) {
      pos++;
    }
    if (isalpha(src[pos])) {
      return word();
    } else if (isdigit(src[pos]) || src[pos] == '-' || src[pos] == '.') {
      return number();
    } else if (src[pos] == '{') {
      pos++;
      return Token{TokenType::LParen, "{"};
    } else if (src[pos] == '}') {
      pos++;
      return Token{TokenType::RParen, "}"};
    } else {
      throw std::runtime_error("Unexpected token");
    }
  }
  Sphere constructSphere();
  Light constructLight();
  Point constructCamera();
  Color constructColor();
  Point constructPoint();
  Token consume(TokenType);
};

void SceneParser::tokenize() {
  while (pos != src.length()) {
    tokens.push_back(scanToken());
  }
}

/** Take off token, expecting this value. */
Token SceneParser::consume(TokenType t) {
  if(tokens.front().type == t) {
    auto t = tokens.front();
    tokens.pop_front();
    return t;
  } else {
    throw std::runtime_error(tokens.front().datum);
  }
}

Point SceneParser::constructPoint() {
  double x = stod(consume(TokenType::Number).datum);
  double y = stod(consume(TokenType::Number).datum);
  double z = stod(consume(TokenType::Number).datum);
  return Point(x, y, z);
}

Color SceneParser::constructColor() {
  uint8_t x = stoi(consume(TokenType::Number).datum);
  uint8_t y = stoi(consume(TokenType::Number).datum);
  uint8_t z = stoi(consume(TokenType::Number).datum);
  return Color(x, y, z);
}
Sphere SceneParser::constructSphere() {
  consume(TokenType::LParen);
  Point origin = constructPoint();
  int radius = stoi(consume(TokenType::Number).datum);
  Color color = constructColor();
  consume(TokenType::RParen);
  return Sphere(origin, radius, color);
}
LightType getLightType(const std::string& s) {
  if(s == "AMBIENT") return LightType::AMBIENT;
  if(s == "POINT") return LightType::POINT;
  if(s == "DIRECTIONAL") return LightType::DIRECTIONAL;
  return LightType::AMBIENT;
}
Light SceneParser::constructLight() {
  consume(TokenType::LParen);
  Point origin = constructPoint();
  double intensity = stod(consume(TokenType::Number).datum);
  LightType type = getLightType(consume(TokenType::Word).datum);
  consume(TokenType::RParen);
  return Light(origin, intensity, type);
}
Point SceneParser::constructCamera() {
  consume(TokenType::LParen);
  Point origin = constructPoint();
  consume(TokenType::RParen);
  return origin;
}

Scene SceneParser::parse() {
  tokenize();
  while (tokens.size()) {
    auto token = tokens.front();
    tokens.pop_front();
    if (token.datum == "Sphere") {
      auto sphere = constructSphere();
      scene.spheres.push_back(sphere);
    } else if (token.datum == "Light") {
      auto light = constructLight();
      scene.lights.push_back(light);
    } else if (token.datum == "Camera") {
      auto camera = constructCamera();
      scene.camera = camera;
    } else {
      throw std::runtime_error("Unexpected token recieved: " + token.datum);
    }
  }
  return scene;
}