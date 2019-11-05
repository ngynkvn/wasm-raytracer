#ifndef COLOR_H
#define COLOR_H
#include "defs.h"

Color trace_ray(const Scene &, const Point &dir, double t_min, double t_max);
#endif