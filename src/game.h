// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <string>
#include <vector>

#include "enemy.h"
#include "item.h"
#include "log.h"
#include "map.h"
#include "player.h"
#include "ui.h"

class Game {
public:
  Game(); // Initializes the game

  // Singleton access
  static Game &getInstance() {
    static Game instance;
    return instance;
  }

  void run();                      // Starts the main game loop
  void reset();                    // Resets game state and restarts the game
  void movePlayer(int dx, int dy); // Attempts to move the player
  void resetFOV();                 // Updates field of view around the player
  void moveEnemies();              // Moves enemies based on basic AI
  void checkCollisions(); // Resolves player interactions with enemies and items

private:
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

  UI ui; // Manages UI rendering

  // Game windows
  WINDOW *main_win = newwin(LINES, COLS, 0, 0); // Full-screen container
  WINDOW *viewport_win =
      newwin(ui.VIEWPORT_HEIGHT, ui.VIEWPORT_WIDTH, 0, 0); // Main game area
  WINDOW *log_win = newwin(Log::LOG_LINES + 2, COLS, ui.VIEWPORT_HEIGHT + 1,
                           0); // Command log area
  WINDOW *info_win =
      newwin(10, 20, 0, ui.VIEWPORT_WIDTH + 1); // Player info panel
};

#endif // GAME_H
