// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "log.h"

// Adds a new log entry, replacing the oldest if the log is full
void Log::log_command(const std::string &command) {
  if (command_log.size() < LOG_LINES) {
    command_log.push_back(command);
  } else {
    command_log[log_index] = command;
  }
  log_index = (log_index + 1) % LOG_LINES;
}
