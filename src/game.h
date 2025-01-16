// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "map.h"
#include "enemy.h"
#include "player.h"
#include "item.h"
#include "ui.h"

class Game {
public:
    Game();                                       // Default constructor
    void run();                                   // Main game loop
    void movePlayer(int dx, int dy);              // Move the player
    void resetFOV();                              // Reset field of view
    void placeEnemies();                          // Randomly place enemies 
    void placeItems();                            // Randomly place items
    void moveEnemies();                           // Move enemies
    void checkCollisions();                       // Check for collisions
    void log_command(const std::string &command); // Log a command message

private:
    Map map;                              // The game map
    UI ui;                                // User interface handler
    std::vector<std::string> command_log; // Log of commands
    int log_index = 0;                    // Current index for the command log
    Player player;                        // The player character
    std::vector<Enemy> enemies;           // List of enemies
    std::vector<Item> items;              // List of items
};

#endif // GAME_H
