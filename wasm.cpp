#include <vector>
#include <emscripten/bind.h>
#include "defs.h"
#include "scene.h"
#include "raytracer.h"

using namespace emscripten;

std::vector<uint8_t> draw() {
  std::vector<uint8_t> buffer(Cw * Ch * 4);
  int ptr = 0;
  auto canvas_to_viewport = [&](double x, double y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };
  auto CwO = Cw / 2;
  auto ChO = Ch / 2;
  for (int y = Ch / 2; y > -Ch / 2; y--) {
    for (int x = -Cw / 2; x < Cw / 2; x++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(scene_camera, dir, 0, 2000);
      buffer[ptr++] = color.r;
      buffer[ptr++] = color.g;
      buffer[ptr++] = color.b;
      buffer[ptr++] = 255;
    }
  }
  return buffer;
}

EMSCRIPTEN_BINDINGS(m) {
  function("draw", &draw);
  register_vector<uint8_t>("vector<uint8_t>");
}
