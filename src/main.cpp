#include "core/astar/astar.hpp"
#include "core/grid/GridLocation.hpp"
#include "core/grid/grid.hpp"
#include "visualization/renderer.hpp"

using namespace astar::core;

Grid create_maze() {
  Grid grid{30, 20, {}};

  // vertical walls
  for (int y = 2; y < 18; y++)
    grid.walls.insert({5, y});
  for (int y = 0; y < 12; y++)
    grid.walls.insert({10, y});
  for (int y = 8; y < 20; y++)
    grid.walls.insert({15, y});
  for (int y = 2; y < 15; y++)
    grid.walls.insert({20, y});
  for (int y = 6; y < 20; y++)
    grid.walls.insert({25, y});

  // horizontal walls
  for (int x = 0; x < 8; x++)
    grid.walls.insert({x, 8});
  for (int x = 7; x < 15; x++)
    grid.walls.insert({x, 14});
  for (int x = 12; x < 22; x++)
    grid.walls.insert({x, 5});
  for (int x = 17; x < 28; x++)
    grid.walls.insert({x, 12});
  for (int x = 22; x < 30; x++)
    grid.walls.insert({x, 3});

  // oenings in walls (remove some wall cells to create passages)
  grid.walls.erase({5, 5});
  grid.walls.erase({5, 12});
  grid.walls.erase({5, 16});
  grid.walls.erase({10, 8});
  grid.walls.erase({10, 10});
  grid.walls.erase({15, 10});
  grid.walls.erase({15, 15});
  grid.walls.erase({20, 6});
  grid.walls.erase({20, 12});
  grid.walls.erase({25, 8});
  grid.walls.erase({25, 15});

  // extra obstacles for visual interest
  grid.walls.insert({3, 4});
  grid.walls.insert({3, 5});
  grid.walls.insert({7, 2});
  grid.walls.insert({7, 3});
  grid.walls.insert({12, 17});
  grid.walls.insert({13, 17});
  grid.walls.insert({22, 8});
  grid.walls.insert({23, 8});
  grid.walls.insert({27, 16});
  grid.walls.insert({27, 17});

  return grid;
}

int main() {
  Grid grid = create_maze();
  GridLocation start{1, 1};
  GridLocation goal{28, 18};

  SearchResult result = find_path_animated(grid, start, goal);

  astar::viz::Renderer renderer(900, 640, grid);
  renderer.run(start, goal, result);

  return 0;
}
