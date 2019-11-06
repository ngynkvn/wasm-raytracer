#include "defs.h"
#include "raytracer.h"
#include "scene_parser.h"
#include <emscripten/bind.h>
#include <string>
#include <vector>

using namespace emscripten;



Scene scene_from_str(const std::string &str) {
  SceneParser sp(str);
  return sp.parse();
};


static Scene scene;
void setScene(const std::string& str) {
  scene = scene_from_str(str);
}

Point canvas_to_viewport(double x, double y) {
  return Point(x * scene.ViewWidth / scene.width, y * scene.ViewHeight / scene.height, scene.z_dist);
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

ColorStruct trace(double x, double y) {
  auto dir = canvas_to_viewport(x, y);
  return to_struct(trace_ray(scene, dir, 0, 2000));
}

std::vector<uint8_t> create_vec_from(const std::string& str) {  
  setScene(str);
  std::vector<uint8_t> buffer(scene.width * scene.height * 4);
  
  size_t ptr = 0;
  for (int y = scene.height / 2; y > -scene.height / 2; y--) {
    for (int x = -scene.width / 2; x < scene.width / 2; x++) {
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

uint8_t* getBuffer(int size) {
  static uint8_t* buffer;
  static int size_buffer = -1;
  if(size_buffer < size) {
    free(buffer);
    buffer = (uint8_t *)malloc(size * sizeof(uint8_t));
    size_buffer = size;
  }
  return buffer;
}


val create_view_from(const std::string &str) {
  setScene(str);
  uint8_t* buffer = getBuffer(scene.height * scene.width * 4);
  size_t ptr = 0;
  for (int y = scene.height / 2; y > -scene.height / 2; y--) {
    for (int x = -scene.width / 2; x < scene.width / 2; x++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(scene, dir, 0, 2000);
      buffer[ptr++] = color.r;
      buffer[ptr++] = color.g;
      buffer[ptr++] = color.b;
      buffer[ptr++] = 255;
    }
  }
  return val(typed_memory_view(scene.width * scene.height * 4, buffer));
}

EMSCRIPTEN_BINDINGS(m) {
  function("trace", &trace);
  function("create_vec_from", &create_vec_from);
  function("create_view_from", &create_view_from);
  value_array<ColorStruct>("Color")
      .element(&ColorStruct::r)
      .element(&ColorStruct::g)
      .element(&ColorStruct::b);
  register_vector<uint8_t>("ColorVec");
}