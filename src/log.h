// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef LOG_H
#define LOG_H

#include <ncurses.h>
#include <string>
#include <vector>

class Log {
public:
  static const int LOG_LINES = 5; // Maximum number of log messages to retain

  // Singleton access method
  static Log &getInstance() {
    static Log instance;
    return instance;
  }

  int log_index = 0; // Index for the next log message

  // Adds a command to the log
  void log_command(const std::string &command);

  // Stores log messages
  std::vector<std::string> command_log;

private:
  Log() {}                              // Private constructor
  ~Log() {}                             // Private destructor
  Log(const Log &) = delete;            // Disable copy constructor
  Log &operator=(const Log &) = delete; // Disable copy assignment
};

#endif // LOG_H
