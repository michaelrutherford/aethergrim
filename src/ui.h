// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef UI_H
#define UI_H

#include "enemy.h"
#include "item.h"
#include "log.h"
#include "map.h"
#include "player.h"
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

class UI {
public:
  static const int VIEWPORT_WIDTH = 30;  // Width of the game viewport
  static const int VIEWPORT_HEIGHT = 15; // Height of the game viewport

  UI();  // Default constructor
  ~UI(); // Destructor

  // Initialize the NCurses window
  void initialize();

  // Print text with word wrapping
  void wrapPrint(WINDOW *win, const std::string &text, int start_y, int start_x,
                 int width);

  // Functions for drawing UI elements on screen
  void drawMenu(WINDOW *win);
  void drawHelp();
  void drawCredits();
  void drawViewport(WINDOW *win, const Player &player,
                    const std::vector<Enemy> &enemies,
                    const std::vector<Item> &items, const Map &map);
  void drawLog(WINDOW *win, Log &log, size_t logIndex);
  void drawInfo(WINDOW *win, const Player &player);
  void drawInventory(WINDOW *win, Player &player);
  void drawItemDetails(Player &player, size_t index);
  void drawQuit();
  void drawGameOver(WINDOW *win);

private:
  void setupColors(); // Set up color pairs for the UI
};

#endif // UI_H
