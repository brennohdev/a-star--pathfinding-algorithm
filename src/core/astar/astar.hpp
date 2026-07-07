#pragma once

#include "core/astar/search_result.hpp"
#include "core/grid/GridLocation.hpp"
#include "core/grid/grid.hpp"
#include <vector>

namespace astar::core {

std::vector<GridLocation> find_path(const Grid &grid, const GridLocation &start,
                                    const GridLocation &goal);

SearchResult find_path_animated(const Grid &grid, const GridLocation &start,
                                const GridLocation &goal);

} // namespace astar::core