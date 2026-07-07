#pragma once
#include "core/grid/GridLocation.hpp"
#include <vector>

namespace astar::core {

inline std::vector<GridLocation> reconstruct_path(
    const std::unordered_map<GridLocation, GridLocation> &came_from,
    const GridLocation &start, const GridLocation &goal) {
  std::vector<GridLocation> path;
  GridLocation step = goal;
  while (!(step == start)) {
    path.push_back(step);
    step = came_from.at(step);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

} // namespace astar::core