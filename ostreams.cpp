#include "defs.h"
#include <ostream>
/**
 *   Definitions for ostream operators.
 */
std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << "<" << p.x << ", " << p.y << ", " << p.z << ">";
  return os;
}