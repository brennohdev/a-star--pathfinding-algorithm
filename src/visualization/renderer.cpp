#include "renderer.hpp"
#include <algorithm>

namespace astar::viz {

Renderer::Renderer(int window_width, int window_height, const core::Grid &grid)
    : window_(sf::VideoMode(sf::Vector2u(window_width, window_height)),
              "A* Pathfinding", sf::Style::Close),
      grid_(grid), margin_(2) {

  int available_width = window_width - 40;
  int available_height = window_height - 40;
  cell_size_ =
      std::min(available_width / grid_.width, available_height / grid_.height);

  window_.setFramerateLimit(60);
}

void Renderer::run(const core::GridLocation &start,
                   const core::GridLocation &goal,
                   const core::SearchResult &result) {

  int explored_index = 0;
  int path_index = 0;
  bool exploring_phase = true;
  bool path_phase = false;
  bool done = false;

  sf::Clock clock;
  float explore_speed = 0.02f;
  float path_speed = 0.05f;

  while (window_.isOpen()) {
    while (auto event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
      if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Escape)
          window_.close();
        if (key->code == sf::Keyboard::Key::Space) {
          done = false;
          exploring_phase = true;
          path_phase = false;
          explored_index = 0;
          path_index = 0;
        }
      }
    }

    float elapsed = clock.getElapsedTime().asSeconds();

    if (exploring_phase && elapsed >= explore_speed) {
      clock.restart();
      if (explored_index < static_cast<int>(result.explored_order.size())) {
        explored_index++;
      } else {
        exploring_phase = false;
        path_phase = true;
        clock.restart();
      }
    }

    if (path_phase && elapsed >= path_speed) {
      clock.restart();
      if (path_index < static_cast<int>(result.path.size())) {
        path_index++;
      } else {
        path_phase = false;
        done = true;
      }
    }

    window_.clear(Colors::background);

    draw_grid();
    draw_walls();
    draw_explored(result.explored_order, explored_index);

    if (path_phase || done) {
      draw_path(result.path, path_index);
    }

    draw_endpoints(start, goal);

    window_.display();
  }
}

void Renderer::draw_grid() {
  for (int x = 0; x < grid_.width; x++) {
    for (int y = 0; y < grid_.height; y++) {
      draw_cell(x, y, Colors::empty_cell);
    }
  }
}

void Renderer::draw_cell(int x, int y, const sf::Color &color) {
  float offset_x = 20.0f;
  float offset_y = 20.0f;
  float size = static_cast<float>(cell_size_ - margin_);

  sf::RectangleShape cell(sf::Vector2f(size, size));
  cell.setPosition(sf::Vector2f(offset_x + x * cell_size_ + margin_ / 2.0f,
                                offset_y + y * cell_size_ + margin_ / 2.0f));
  cell.setFillColor(color);
  cell.setOutlineColor(Colors::grid_line);
  cell.setOutlineThickness(1.0f);
  window_.draw(cell);
}

void Renderer::draw_walls() {
  for (const auto &wall : grid_.walls) {
    draw_cell(wall.x, wall.y, Colors::wall);
  }
}

void Renderer::draw_explored(const std::vector<core::GridLocation> &explored,
                             int up_to_index) {
  for (int i = 0; i < up_to_index && i < static_cast<int>(explored.size());
       i++) {
    float progress =
        static_cast<float>(i) / static_cast<float>(explored.size());
    sf::Color color = Colors::explored;
    color.a = static_cast<std::uint8_t>(100 + progress * 100);
    draw_cell(explored[i].x, explored[i].y, color);
  }
}

void Renderer::draw_path(const std::vector<core::GridLocation> &path,
                         int up_to_index) {
  for (int i = 0; i < up_to_index && i < static_cast<int>(path.size()); i++) {
    draw_cell(path[i].x, path[i].y, Colors::path);
  }
}

void Renderer::draw_endpoints(const core::GridLocation &start,
                              const core::GridLocation &goal) {
  draw_cell(start.x, start.y, Colors::start);
  draw_cell(goal.x, goal.y, Colors::goal);
}

} // namespace astar::viz
