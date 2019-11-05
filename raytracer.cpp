#include "defs.h"
#include <optional>
#include <utility>
#include <vector>
/**
 * Solves the quadratic formula of where a ray intersects the surface of a
 * sphere.
 *
 * Derivation comes from:
 *
 * ```
 * radius^2 = |P - center| * |P - center| => <P-center, P-center>
 * P = origin + dir*t
 * ```
 *
 * Plugging p into radius eq and solving for t
 * gives a value t that equals points on surface of the sphere.
 */
std::pair<double, double> intersect_ray_sphere(const Point &origin,
                                               const Point &dir,
                                               const Sphere &sphere) {
  auto oc = origin - sphere.center;

  auto k1 = dir * dir;
  auto k2 = 2.0 * (oc * dir);
  auto k3 = oc * oc - sphere.radius * sphere.radius;

  auto discriminant = k2 * k2 - 4.0 * k1 * k3;
  if (discriminant < 0.0) {
    return std::make_pair(DBL_MAX, DBL_MAX);
  } else {
    auto t1 = (-k2 + std::sqrt(discriminant)) / (2.0 * k1);
    auto t2 = (-k2 - std::sqrt(discriminant)) / (2.0 * k1);
    return std::make_pair(t1, t2);
  }
}

/**
 * Computation of the light vectors is done by computing
 * normal vectors of the surface of the sphere and then
 * taking the dot product
 * with the direction from the light source.
 * Depending on light source type, adjust vector as appropriate.
 */
double compute_lighting(const Point &P, const Point &N, const Scene &scene) {
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

/**
 * Simulate a single ray from point extending outwards in dir.
 * Returns the color for the specific square.
 * This is the algorithm that outputs the colors
 * necessary to create the image.
 */
Color trace_ray(const Scene &scene, const Point &dir, double t_min,
                double t_max) {
  auto t = DBL_MAX;
  std::optional<Sphere> m;
  for (auto &s : scene.spheres) {
    auto t_s = intersect_ray_sphere(scene.camera, dir, s);
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
    auto P = scene.camera + (dir * t);
    auto N = P - m.value().center;
    N = N / N.length();
    return m.value().color * compute_lighting(P, N, scene);
  }
  return WHITE;
}
