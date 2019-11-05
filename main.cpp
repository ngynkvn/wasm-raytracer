#define COUT
#include "raytracer.h"
#include "scene_parser.h"
#include <chrono>
#include <iostream>
#include <png++/png.hpp>
#include <sstream>
/**
 * Create the canvas, a scaling function,
 * then iterate over each pixel
 * and trace the path of ray from camera towards the viewport.
 */
int main() {
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  using std::chrono::system_clock;

  std::string token;
  std::stringstream ss;
  while (std::getline(std::cin, token)) {
    const std::string::size_type position = token.find('\r');
    if (position != std::string::npos) {
      token.erase(position);
    }
    ss << token << '\n';
  }

  SceneParser sp(ss.str());
  Scene s = sp.parse();
  png::image<png::rgb_pixel> image(Cw, Ch);
  auto canvas_to_viewport = [&](double x, double y) {
    return Point(x * Vw / Cw, y * Vh / Ch, z_dist);
  };
  auto CwO = Cw / 2;
  auto ChO = Ch / 2;
  auto start = system_clock::now();
  for (int x = -Cw / 2; x < Cw / 2; x++) {
    for (int y = -Ch / 2; y < Ch / 2; y++) {
      auto dir = canvas_to_viewport(x, y);
      auto color = trace_ray(s, dir, 0, 2000);
      image[ChO - y - 1][x + CwO] = png::rgb_pixel(color.r, color.g, color.b);
    }
  }
  auto stop = system_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  std::cout << "Took " << duration.count() << " ms.";
  image.write("test.png");
  return 0;
}
