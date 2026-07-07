#pragma once
#include <functional>

/**
@brief: This works as a coordinate in a Grid. It only works as postal address.
* I decided to not put nothing here about neighbours, It doesn't know
* what neighbours are.
*/
namespace astar::core {

struct GridLocation {
  int x;
  int y;

  bool operator==(const GridLocation &other) const {
    return x == other.x && y == other.y;
  }
};

} // namespace astar::core

namespace std {
template <> struct hash<astar::core::GridLocation> {
  size_t operator()(const astar::core::GridLocation &loc) const {
    size_t h1 = hash<int>{}(loc.x);
    size_t h2 = hash<int>{}(loc.y);
    return h1 ^ (h2 << 1);
  }
};
} // namespace std
