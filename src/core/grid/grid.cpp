#include "grid.hpp"

namespace astar::core {

bool Grid::in_bounds(const GridLocation &position) const {
  return position.x >= 0 && position.x < width && position.y >= 0 &&
         position.y < height;
};

bool Grid::passable(const GridLocation &position) const {
  return walls.find(position) == walls.end();
};

std::vector<GridLocation> Grid::neighbours(const GridLocation &position) const {
  std::vector<GridLocation> results;

  for (auto direction : DIRECTIONS) {
    GridLocation next = {position.x + direction.x, position.y + direction.y};
    if (in_bounds(next) && passable(next)) {
      results.push_back(next);
    }
  }

  return results;
}
} // namespace astar::core