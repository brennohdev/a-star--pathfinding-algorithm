#pragma once
#include "core/grid/GridLocation.hpp"

namespace astar::core {

struct Node {
  GridLocation position;
  int g_cost;
  int h_cost;
  Node *parent;

  int f_cost() const { return g_cost + h_cost; };
};

} // namespace astar::core
