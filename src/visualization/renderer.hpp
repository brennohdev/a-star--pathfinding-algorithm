#pragma once
#include "core/astar/search_result.hpp"
#include "core/grid/GridLocation.hpp"
#include "core/grid/grid.hpp"
#include <SFML/Graphics.hpp>

namespace astar::viz {

struct Colors {
  static inline const sf::Color background{30, 30, 30};
  static inline const sf::Color empty_cell{50, 50, 60};
  static inline const sf::Color wall{20, 20, 25};
  static inline const sf::Color start{80, 200, 120};
  static inline const sf::Color goal{220, 80, 80};
  static inline const sf::Color path{100, 149, 237};
  static inline const sf::Color explored{255, 200, 60, 180};
  static inline const sf::Color grid_line{40, 40, 50};
};

class Renderer {
public:
  Renderer(int window_width, int window_height, const core::Grid &grid);

  void run(const core::GridLocation &start, const core::GridLocation &goal,
           const core::SearchResult &result);

private:
  sf::RenderWindow window_;
  const core::Grid &grid_;
  int cell_size_;
  int margin_;

  void draw_grid();
  void draw_cell(int x, int y, const sf::Color &color);
  void draw_walls();
  void draw_explored(const std::vector<core::GridLocation> &explored,
                     int up_to_index);
  void draw_path(const std::vector<core::GridLocation> &path, int up_to_index);
  void draw_endpoints(const core::GridLocation &start,
                      const core::GridLocation &goal);
};

} // namespace astar::viz
