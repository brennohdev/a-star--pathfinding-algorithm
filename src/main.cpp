#include "utils/log.hpp"

int main()
{
    using namespace astar::utils;

    Log log;
    log.SetLevel(log.LogLevelError);
    log.Print(LogLevel::LogLevelError, "Hello There");
}