#define COUT
#include "scene.h" //SCENE DEFINITIONS LIVE HERE
#include "raytracer.h"
#include <iostream>
#include <chrono> 
#include <png++/png.hpp>
/**
 * Create the canvas, a scaling function,
 * then iterate over each pixel
 * and trace the path of ray from camera towards the viewport.
 */
int main() {
  using std::chrono::system_clock;
  using std::chrono::milliseconds;
  using std::chrono::duration_cast;

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
      auto color = trace_ray(scene_camera, dir, 0, 2000);
      image[ChO - y - 1][x + CwO] = png::rgb_pixel(color.r, color.g, color.b);
    }
  }
  auto stop = system_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  std::cout << "Took " << duration.count() << " ms.";
  image.write("test.png");
  return 0;
}
