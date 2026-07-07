#pragma once
#include "core/grid/GridLocation.hpp"
#include <vector>

namespace astar::core {

struct SearchResult {
  std::vector<GridLocation> path;
  std::vector<GridLocation> explored_order;
  bool found;
};

} // namespace astar::core
