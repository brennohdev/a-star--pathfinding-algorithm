# A* Pathfinding — from scratch, in C++17

This is the second checkpoint in my self-directed robotics learning path. The goal here was to implement the A* algorithm from scratch, understand the data structures that make it work

The previous project (projectile simulation with aerodynamic drag) gave me the basics of C++ and computational physics. But it used very little STL and zero pointers. A* forced me to work with complex containers, graphs, pointers, and make real architectural decisions.

## Demo

![A* Pathfinding Visualization](https://github.com/user-attachments/assets/8cc068cd-ba99-4fc5-bd91-57ea294267ed)

The visualization shows the algorithm exploring the grid in real time (yellow), then tracing the optimal path found (blue).

**Controls:** `Space` to replay, `Escape` to close.

## What I actually learned

### C++ things I didn't know before this project

- **`const` correctness** — how one keyword changes the entire semantics of a method
- **STL containers** — `priority_queue`, `unordered_set`, `unordered_map` and why each one exists
- **Raw pointers as observers** — the `Node* parent` doesn't own anything, it just points
- **Custom hash** — to use custom types as keys in hash maps
- **Lambda functions** — as a custom comparator for priority_queue

### Algorithms and decisions

- **Why A* and not Dijkstra?** — The heuristic pulls the search toward the goal, exploring fewer nodes. Dijkstra expands in all directions equally.
- **Why `unordered_set` for CLOSED?** — O(1) lookup to check if a node was already processed. With a `vector` it would be O(n) every single check.
- **Why lazy deletion?** — `std::priority_queue` doesn't support removal from the middle. So duplicate nodes stay in the queue and get skipped when they reach the top and are already in CLOSED.
- **Manhattan heuristic** — chosen because the grid is 4-directional. If it were 8 directions, I'd use Euclidean or Chebyshev.

## Architecture

```
src/
├── core/                 ← pure algorithm, no external dependencies
│   ├── astar/            ← find_path, reconstruct_path, search_result
│   ├── grid/             ← Grid, GridLocation (value object with hash)
│   ├── node.hpp          ← struct with position, costs, and parent pointer
│   └── heuristic.hpp     ← Manhattan distance (inline, header-only)
├── visualization/        ← SFML renderer (not part of core)
├── utils/                ← logging system with level filtering
└── main.cpp              ← assembles the grid, runs A*, passes result to renderer
```

The main architectural decision: **core does no IO**. It doesn't print, doesn't draw, doesn't read files. This means I can swap the visualization layer (terminal, SFML, another lib) without touching the algorithm. And the A* is testable in isolation.

## Challenges I faced

- **Understanding C++'s priority_queue** — it gives the LARGEST element by default, and I needed the smallest f. The comparator inverts with `>` instead of `<`. Seems simple, but it confused me at first.

## How to build

The project uses CMake's FetchContent to download SFML automatically. You don't need to install SFML manually — just have CMake 3.20+ and a C++17 compiler.

### Quick build (recommended)

```bash
git clone https://github.com/brennohdev/a-star--pathfinding-algorithm.git
cd a-star--pathfinding-algorithm
./build.sh
./build/app
```

### Manual build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/app
```

### Docker

If you don't want to install anything locally:

```bash
docker build -t astar .
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix astar
```

> Note: Docker with GUI requires X11 forwarding. On macOS you'd need XQuartz. On Linux it works out of the box. The Docker build is mainly useful for verifying the project compiles in a clean environment.

### Prerequisites

| Tool | Minimum version | Notes |
|------|----------------|-------|
| CMake | 3.20 | Build system |
| C++ compiler | C++17 support | GCC 8+, Clang 7+, MSVC 19.14+ |
| Git | any | FetchContent clones SFML during build |

SFML 3.0.2 is fetched and built automatically by CMake. No manual installation required.

### Platform support

| Platform | Status | Notes |
|----------|--------|-------|
| macOS (ARM/Intel) | ✅ | Tested on Apple Silicon |
| Linux (X11) | ✅ | Requires OpenGL and X11 dev packages |
| Windows | not tested | maybe Works with MSVC or MinGW |

For Linux, if the build fails on missing system libraries:
```bash
sudo apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libudev-dev libfreetype-dev libopenal-dev libvorbis-dev libflac-dev libgl1-mesa-dev
```

## References

- [Sebastian Lague — A* Pathfinding (YouTube)](https://www.youtube.com/watch?v=-L-WgKMFuhE) — the visual explanation that made the algorithm click in my head
- [Red Blob Games — Introduction to A*](https://www.redblobgames.com/pathfinding/a-star/introduction.html) — interactive text reference with step-by-step visualizations
- [Red Blob Games — Implementation in C++](https://www.redblobgames.com/pathfinding/a-star/implementation.html) — helped me understand graph structure in code

## AI Disclosure

I used AI as a learning tool throughout this project. Specifically:

- **What AI did:** helped me understand C++ concepts (namespaces, pointers, const, templates), reviewed my code pointing out errors and explaining why, and wrote the visualization layer (SFML) and this README.
- **What I did:** all architecture decisions, the A* algorithm implementation (with its mistakes and corrections along the way), the data structures (Grid, Node, GridLocation), and the logic of every method.

The AI worked as a private tutor, it explained concepts, gave me hints when I got stuck, and redirected me when I asked for ready-made answers. The core code is mine, mistakes included in the learning process.

---

*Checkpoint 2 of 7 in my autonomous robotics learning path.*
*Next up: Differential drive robot with PID control.*
