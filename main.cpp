#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <optional>
#include <png++/png.hpp>
#include <utility>
#include <vector>

struct Point {
  double x;
  double y;
  double z;
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
  Point() : x(0), y(0), z(0) {}
  Point operator+(const Point &other) {
    return Point(x + other.x, y + other.y, z + other.z);
  }

  Point operator-(const Point &other) {
    return Point(x - other.x, y - other.y, z - other.z);
  }

  double operator*(const Point &other) {
    return x * other.x + y * other.y + z * other.z;
  }

  double length() { return std::sqrt((*this) * (*this)); }

  Point operator/(double value) {
    return Point(x / value, y / value, z / value);
  }
  Point operator*(double value) {
    return Point(x * value, y * value, z * value);
  }
};
std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << "<" << p.x << ", " << p.y << ", " << p.z << ">";
  return os;
}

struct Color {
  int r;
  int g;
  int b;
  Color(int r, int g, int b) : r(r), g(g), b(b) {}
  Color operator*(double value) {
    return Color(r * value, g * value, b * value);
  }
};
const Color white(255, 255, 255);

enum LightType { AMBIENT, POINT, DIRECTIONAL };
struct Light {
  Point vector;
  double intensity;
  LightType type;
  Light(Point vector, double intensity, LightType type)
      : vector(vector), intensity(intensity), type(type) {}
};

struct Sphere {
  Point origin;
  double radius;
  Color color;
  Sphere(Point origin, double radius, Color color)
      : origin(origin), radius(radius), color(color) {}
};

struct Scene {
  std::vector<Sphere> spheres;
  std::vector<Light> lights;
  Scene() {
    spheres.emplace_back(Point(0, -1, 3), 1, Color(255, 0, 0));
    spheres.emplace_back(Point(2, 0, 4), 1, Color(0, 255, 0));
    spheres.emplace_back(Point(-2, 0, 4), 1, Color(0, 0, 255));
    spheres.emplace_back(Point(0, -5001, 0), 5000, Color(0, 255, 255));
    lights.emplace_back(Point(0, 0, 0), .2, AMBIENT);
    lights.emplace_back(Point(2, 1, 0), .6, POINT);
    lights.emplace_back(Point(1, 4, 4), .2, DIRECTIONAL);
  }
};
Scene scene;

std::pair<double, double> intersect_ray_sphere(Point &origin, Point &dir,
                                               Sphere &sphere) {
  auto center = sphere.origin;
  auto radius = sphere.radius;
  auto oc = origin - center;

  auto k1 = dir * dir;
  auto k2 = 2.0 * (oc * dir);
  auto k3 = oc * oc - radius * radius;

  auto discriminant = k2 * k2 - 4.0 * k1 * k3;
  if (discriminant < 0.0) {
    return std::make_pair(DBL_MAX, DBL_MAX);
  } else {
    auto t1 = (-k2 + std::sqrt(discriminant)) / (2.0 * k1);
    auto t2 = (-k2 - std::sqrt(discriminant)) / (2.0 * k1);
    return std::make_pair(t1, t2);
  }
}

double compute_lighting(Point P, Point N) {
  auto i = 0.0;
  for (auto &l : scene.lights) {
    if (l.type == AMBIENT) {
      i += l.intensity;
    } else {
      Point L;
      if (l.type == POINT) {
        L = l.vector - P;
      } else if (l.type == DIRECTIONAL) {
        L = l.vector;
      }
      double dot = N * L;
      if (dot > 0) {
        i += (l.intensity * dot) / (N.length() * L.length());
      }
    }
  }
  return i;
}

Color trace_ray(Point &origin, Point &dir, double t_min, double t_max) {
  auto t = DBL_MAX;
  std::optional<Sphere> m;
  for (auto &s : scene.spheres) {
    auto t_s = intersect_ray_sphere(origin, dir, s);
    auto fst = t_s.first;
    auto snd = t_s.second;
    if (fst < t && t_min < fst && fst < t_max) {
      t = fst;
      m = s;
    }
    if (snd < t && t_min < snd && snd < t_max) {
      t = snd;
      m = s;
    }
  }
  if (m) {
    auto P = origin + (dir * t);
    auto N = P - m.value().origin;
    N = N / N.length();
    return m.value().color * compute_lighting(P, N);
  }
  return white;
}

int main() {
  auto CameraPosition = Point(0, 0, 0);
  auto Cw = 200;
  auto Ch = 200;
  auto Vw = 1;
  auto Vh = 1;
  auto z_dist = 1;
  png::image<png::rgb_pixel> image(Cw, Ch);
  auto canvas_to_viewport = [&](double x, double y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };
  auto CwO = Cw / 2;
  auto ChO = Ch / 2;
  for (int x = -Cw / 2; x < Cw / 2; x++) {
    for (int y = -Ch / 2; y < Ch / 2; y++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(CameraPosition, dir, 0, 2000);
      image[ChO - y - 1][x + CwO] = png::rgb_pixel(color.r, color.g, color.b);
    }
  }
  image.write("test.png");
  return 0;
}
