// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <sstream>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "map.h"

class UI {
public:
    static const int VIEWPORT_WIDTH = 30;  // Width of the game viewport
    static const int VIEWPORT_HEIGHT = 15; // Height of the game viewport
    static const int LOG_LINES = 5;        // Number of lines in command log

    UI();  // Default constructor
    ~UI(); // Destructor
    
    // Initialize the NCurses window
    void initialize();

    // Print text with word wrapping
    void wrapPrint(WINDOW *win, const std::string &text, 
                   int start_y, int start_x, int width); 

    // Functions for drawing UI elements on screen
    void drawMenu(WINDOW *win);
    void drawViewport(WINDOW *win, const Player &player, 
                                   const std::vector<Enemy> &enemies, 
                                   const std::vector<Item> &items, 
                                   const Map &map);
    void drawLog(WINDOW *win, const std::vector<std::string> &commandLog,
                 size_t logIndex);
    void drawInfo(WINDOW *win, const Player &player);
    void drawInventory(WINDOW *win, const Player &player);

private:
    void setupColors(); // Set up color pairs for the UI
};

#endif // UI_H
