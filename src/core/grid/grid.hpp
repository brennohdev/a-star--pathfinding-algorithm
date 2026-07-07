#pragma once
#include "GridLocation.hpp"
#include <unordered_set>
#include <vector>

namespace astar::core {

inline constexpr GridLocation DIRECTIONS[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

/**
 *@brief: This represents a Grid.
 * Return true if position is inside of the limits
 * Return true if position is not a wall
 * Return the valid neighbours (inside limits and passables)
 */
struct Grid {
  int width, height;
  std::unordered_set<GridLocation> walls;

  bool in_bounds(const GridLocation &position) const;
  bool passable(const GridLocation &position) const;

  std::vector<GridLocation> neighbours(const GridLocation &position) const;
};
} // namespace astar::core
