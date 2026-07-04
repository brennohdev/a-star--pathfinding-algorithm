#include <iostream>
#include "log.hpp"

namespace astar::utils {

    
    void Log::SetLevel(int level)
    {
        m_LogLevel = level;
    }

    void Log::Print(int level, const char* message) const
    {
    if (level > m_LogLevel) return;

    const char* prefix;

    switch (level) {
        case 0: prefix = "[ERROR] "; break;
        case 1: prefix = "[WARN]  "; break;
        case 2: prefix = "[INFO]  "; break;
        default: return;
    }

    std::cout << prefix << message << std::endl;
    }

}