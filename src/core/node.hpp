#include <unordered_map>
#include <vector>

namespace astar {

    struct SimpleGraph {
    std::unordered_map<char, std::vector<char> > edges;

    std::vector<char> neighbors(char id)
    {
            return edges[id];
    }
    };

}

