#ifndef DEFS_H
#define DEFS_H
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <vector>
#include <utility>

/**
 *   Simple 3-d point / vector struct with operations implemented for
 *   addition, subtraction, dot product, and scaling.
 */
struct Point {
  double x;
  double y;
  double z;
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
  Point() : x(0), y(0), z(0) {}
  Point operator+(const Point &other) const {
    return Point(x + other.x, y + other.y, z + other.z);
  }

  Point operator-(const Point &other) const {
    return Point(x - other.x, y - other.y, z - other.z);
  }

  double operator*(const Point &other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  double length() const { return std::sqrt((*this) * (*this)); }

  Point operator/(double value) const {
    return Point(x / value, y / value, z / value);
  }
  Point operator*(double value) const {
    return Point(x * value, y * value, z * value);
  }
};
std::ostream &operator<<(std::ostream &os, const Point &p);

/**
 * Color of RGB values
 */
struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
  Color operator*(double value) {
    return Color(r * value, g * value, b * value);
  }
};
/**
 * Color constants
 */
const Color WHITE(255, 255, 255);
const Color RED(255, 0, 0);
const Color GREEN(0, 255, 0);
const Color BLUE(0, 0, 255);

enum LightType { AMBIENT, POINT, DIRECTIONAL };
struct Light {
  Point vector;
  double intensity;
  LightType type;
  Light(Point vector, double intensity, LightType type)
      : vector(vector), intensity(intensity), type(type) {}
};

/**
 * Sphere defined by a center and a radius.
 * Color attribute is used for render
 */
struct Sphere {
  Point center;
  double radius;
  Color color;
  Sphere(Point center, double radius, Color color)
      : center(center), radius(radius), color(color) {}
};

#endif