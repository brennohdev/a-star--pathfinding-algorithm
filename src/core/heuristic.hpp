#pragma once
#include "core/grid/GridLocation.hpp"
#include <cstdlib>

namespace astar::core {

inline int manhattan_distance(const GridLocation &a, const GridLocation &b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

} // namespace astar::core
