#ifndef SCENE_H
#define SCENE_H
#include "defs.h"
#include <iostream>

#define Cw  2000
#define Ch  2000
#define Vw  1
#define Vh  1
#define z_dist 1
/**
 * Definitions of the scene.
 * This is what is actually being rendered.
 */
const Point scene_camera = Point(0, 0, 0);

const std::vector<Sphere> scene_spheres = {
    Sphere(Point(0, -1, 3), 1, RED),
    Sphere(Point(2, 0, 4), 1, GREEN),
    Sphere(Point(-2, 0, 4), 1, BLUE),
    Sphere(Point(0, -5001, 0), 5000, Color(0, 255, 255))
};
const std::vector<Light> scene_lights = {
    Light(Point(0, 0, 0), .2, AMBIENT),
    Light(Point(2, 1, 0), .6, POINT),
    Light(Point(1, 4, 4), .2, DIRECTIONAL)
};

#endif