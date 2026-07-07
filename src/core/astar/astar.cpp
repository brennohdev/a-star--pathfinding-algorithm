#include "astar.hpp"
#include "core/astar/reconstruct_path.hpp"
#include "core/grid/GridLocation.hpp"
#include "core/heuristic.hpp"
#include "core/node.hpp"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar::core {

std::vector<GridLocation> find_path(const Grid &grid, const GridLocation &start,
                                    const GridLocation &goal) {
  auto result = find_path_animated(grid, start, goal);
  return result.path;
}

SearchResult find_path_animated(const Grid &grid, const GridLocation &start,
                                const GridLocation &goal) {

  auto compare = [](const Node &a, const Node &b) {
    return a.f_cost() > b.f_cost();
  };

  std::priority_queue<Node, std::vector<Node>, decltype(compare)> open(compare);
  std::unordered_set<GridLocation> closed;
  std::unordered_map<GridLocation, GridLocation> came_from;
  std::unordered_map<GridLocation, int> g_costs;
  std::vector<GridLocation> explored_order;

  g_costs[start] = 0;
  Node start_node{start, 0, manhattan_distance(start, goal), nullptr};
  open.push(start_node);

  while (!open.empty()) {
    Node current = open.top();
    open.pop();

    if (closed.count(current.position))
      continue;

    explored_order.push_back(current.position);

    if (current.position == goal) {
      auto path = reconstruct_path(came_from, start, goal);
      return SearchResult{path, explored_order, true};
    }

    closed.insert(current.position);

    for (auto neighbour_position : grid.neighbours(current.position)) {
      int new_g = g_costs[current.position] + 1;

      if (!g_costs.count(neighbour_position) ||
          new_g < g_costs[neighbour_position]) {
        g_costs[neighbour_position] = new_g;
        int h = manhattan_distance(neighbour_position, goal);
        Node neighbour{neighbour_position, new_g, h, nullptr};
        open.push(neighbour);
        came_from[neighbour_position] = current.position;
      }
    }
  }

  return SearchResult{{}, explored_order, false};
}

} // namespace astar::core