/* 
* Aethergrim
* Copyright (C) 2024- Michael Rutherford
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
