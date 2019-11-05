#include <vector>
#include <emscripten/bind.h>
#include "defs.h"
#include "scene.h"
#include <string>
#include "raytracer.h"

using namespace emscripten;

Scene scene_from_str(const std::string& str);
Point canvas_to_viewport(double x, double y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };

struct ColorStruct {
  double r;
  double g;
  double b;
};

ColorStruct to_struct(Color c) {
  ColorStruct cs;
  cs.r = c.r;
  cs.g = c.g;
  cs.b = c.b;
  return cs;
}
const Scene scene = {scene_camera, scene_spheres, scene_lights};
ColorStruct trace(double x, double y) {
  auto dir = canvas_to_viewport(x, y);
  return to_struct(trace_ray(scene, dir, 0, 2000));
}

std::vector<uint8_t> create_vec() {
  std::vector<uint8_t> buffer(Cw * Ch * 4);
  size_t ptr = 0;
  auto canvas_to_viewport = [&](double x, double y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };
  for (int y = Ch / 2; y > -Ch / 2; y--) {
    for (int x = -Cw / 2; x < Cw / 2; x++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(scene, dir, 0, 2000);
      buffer[ptr++] = color.r;
      buffer[ptr++] = color.g;
      buffer[ptr++] = color.b;
      buffer[ptr++] = 255;
    }
  }
  return buffer;
}

val create_view() {
  static uint8_t buffer[Cw * Ch * 4];
  size_t ptr = 0;
  for (int y = Ch / 2; y > -Ch / 2; y--) {
    for (int x = -Cw / 2; x < Cw / 2; x++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(scene, dir, 0, 2000);
      buffer[ptr++] = color.r;
      buffer[ptr++] = color.g;
      buffer[ptr++] = color.b;
      buffer[ptr++] = 255;
    }
  }
  return val(typed_memory_view(Cw * Ch * 4, buffer));
}

val create_view_from(const std::string& str) {
  static uint8_t buffer[Cw * Ch * 4];
  size_t ptr = 0;
  Scene scene = scene_from_str(str);
  for (int y = Ch / 2; y > -Ch / 2; y--) {
    for (int x = -Cw / 2; x < Cw / 2; x++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(scene, dir, 0, 2000);
      buffer[ptr++] = color.r;
      buffer[ptr++] = color.g;
      buffer[ptr++] = color.b;
      buffer[ptr++] = 255;
    }
  }
  return val(typed_memory_view(Cw * Ch * 4, buffer));
}


EMSCRIPTEN_BINDINGS(m) {
  function("create_vec", &create_vec);
  function("trace", &trace);
  function("create_view", &create_view);
  function("create_view_from", &create_view_from);
  value_array<ColorStruct>("Color")
    .element(&ColorStruct::r)
    .element(&ColorStruct::g)
    .element(&ColorStruct::b);
  register_vector<uint8_t>("ColorVec");
}
