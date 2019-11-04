#include <algorithm>
#include <cfloat>
#include <cmath>
#include <vector>

struct Point {
  double x;
  double y;
  double z;
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
  Point operator+(const Point &other) {
    return Point(x + other.x, y + other.y, z - other.z);
  }

  Point operator-(const Point &other) {
    return Point(x - other.x, y - other.y, z - other.z);
  }

  double operator*(const Point &other) {
    return x * other.x + y * other.y + z * other.z;
  }
};

struct Sphere {
  Point origin;
  double radius;
  int color;
  Sphere(Point origin, double radius, int color) : origin(origin), radius(radius), color(color) {}
};

double intersect_ray_sphere(Point &origin, Point &dir, Sphere &sphere) {
  auto center = sphere.origin;
  auto radius = sphere.radius;
  auto oc = origin - center;

  auto k1 = dir * dir;
  auto k2 = 2.0 * (oc * dir);
  auto k3 = oc * oc - radius * radius;

  auto discriminant = k2 * k2 - 4.0 * k1 * k3;
  if (discriminant < 0.0) {
    return DBL_MAX;
  } else {
    auto t1 = (-k2 + std::sqrt(discriminant)) / (2.0 * k1);
    auto t2 = (-k2 - std::sqrt(discriminant)) / (2.0 * k1);
    return std::min(t1, t2);
  }
}

int trace_ray(Point &origin, Point &dir, double t_min, double t_max,
              std::vector<Sphere> &spheres) {
  auto intersect = [&](Sphere &a, Sphere &b) {
    return intersect_ray_sphere(origin, dir, a) <
           intersect_ray_sphere(origin, dir, b);
  };
  Sphere m = *std::min_element(spheres.begin(), spheres.end(), intersect);
  if (intersect_ray_sphere(origin, dir, m) != DBL_MAX) {
    return m.color;
  }
  return 0xFFFFFF;
}

int main() {
  auto CameraPosition = Point(0, 0, 0);
  auto Cw = 400;
  auto Ch = 400;
  auto Vw = 1;
  auto Vh = 1;
  auto z_dist = 1;
  int canvas[Ch][Cw];
  std::vector<Sphere> spheres;
  spheres.emplace_back(Point(0, -1, 3), 1, 0xFF0000);
  spheres.emplace_back(Point(2, 0, 4), 1, 0x00FF00);
  spheres.emplace_back(Point(-2, 0, 4), 1, 0x0000FF);
  auto canvas_to_viewport = [&](int x, int y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };
  for (int x = -Vw / 2; x < Vw / 2; x++) {
    for (int y = -Vh / 2; y < Vh / 2; y++) {
      auto dir = canvas_to_viewport(x, y);
      canvas[y][x] = trace_ray(CameraPosition, dir, 0, 1000, spheres);
    }
  }
  return 0;
}
