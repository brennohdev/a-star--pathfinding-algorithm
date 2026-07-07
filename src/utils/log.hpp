#pragma once

namespace astar::utils {

enum LogLevel { LogLevelError = 0, LogLevelWarning = 1, LogLevelInfo = 2 };

class Log {
public:
  const int LogLevelError = 0;
  const int LogLevelWarning = 1;
  const int LogLevelInfo = 2;

private:
  int m_LogLevel = LogLevelInfo;

public:
  void SetLevel(int level);
  void Print(int level, const char *message) const;
};
} // namespace astar::utils
