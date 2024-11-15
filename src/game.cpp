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

#include "game.h"

// Default constructor
Game::Game() {
    // Set player location to the designated spawn point
    player.setXCoordinate(map.getSpawnX());
    player.setYCoordinate(map.getSpawnY());
}

// Main game loop
void Game::run() {
    srand(time(NULL)); // Seed random number generator

    // Initialize player spawn position
    player.setXCoordinate(map.getSpawnX());
    player.setYCoordinate(map.getSpawnY());

    // Create windows
    WINDOW *main_win = newwin(LINES, COLS, 0, 0);
    WINDOW *viewport_win = newwin(ui.VIEWPORT_HEIGHT, ui.VIEWPORT_WIDTH, 0, 0);
    WINDOW *log_win = newwin(ui.LOG_LINES + 2, COLS, ui.VIEWPORT_HEIGHT + 1, 0);
    WINDOW *info_win = newwin(10, 20, 0, ui.VIEWPORT_WIDTH + 1);

    ui.drawMenu(main_win); // Draw the main menu

    // Place enemies and items on the map
    placeEnemies();
    placeItems();

    log_command("Welcome to the Sunken Ruins!");

    clear();
    refresh();

    // Game loop
    while (true) {
        resetFOV();           // Reset field of view
        moveEnemies();        // Move enemies based on AI
        checkCollisions();    // Check for player-enemy and player-item collisions

        // Render game state
        ui.drawViewport(viewport_win, player, enemies, items, map);
        ui.drawLog(log_win, command_log, log_index);
        ui.drawInfo(info_win, player);

        // Refresh windows
        wrefresh(viewport_win);
        wrefresh(log_win);
        wrefresh(info_win);

        // Handle player input
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                movePlayer(0, -1);
                break;
            case KEY_DOWN:
                movePlayer(0, 1);
                break;
            case KEY_LEFT:
                movePlayer(-1, 0);
                break;
            case KEY_RIGHT:
                movePlayer(1, 0);
                break;
            case 'i': {
                WINDOW *inventory_win = newwin(12, 50, (LINES - 12) / 2, (COLS - 50) / 2);
                ui.drawInventory(inventory_win, player);
                delwin(inventory_win);
                break;
            }
            case 'q':
                endwin(); // End ncurses mode
                exit(0);  // Exit the game
        }

        // Check if player is defeated
        if (player.getHealth() <= 0) {
            log_command("Game Over! You have been defeated.");
            break;
        }
    }

    endwin(); // End ncurses mode
}

// Reset the field of view for the map
void Game::resetFOV() {
    // Reset all FOV tiles
    for (int y = 0; y < map.MAP_HEIGHT; y++) {
        for (int x = 0; x < map.MAP_WIDTH; x++) {
            map.untoggleFOV(x, y);
        }
    }

    // Mark tiles within FOV as visible
    for (int dy = -player.FOV_Y_RADIUS; dy <= player.FOV_Y_RADIUS; ++dy) {
        for (int dx = -player.FOV_X_RADIUS; dx <= player.FOV_X_RADIUS; ++dx) {
            int map_x = player.getXCoordinate() + dx;
            int map_y = player.getYCoordinate() + dy;
            // Check if within map boundaries
            if (map_y >= 0 && map_y < map.MAP_HEIGHT && map_x >= 0 && map_x < map.MAP_WIDTH) {
                // Only mark as visited if within the FOV radius
                if (dx * dx + dy * dy <= player.FOV_X_RADIUS * player.FOV_X_RADIUS) {
                    map.toggleFOV(map_x, map_y);
                }
            }
        }
    }
}

// Move the player character
void Game::movePlayer(int dx, int dy) {
    int newX = player.getXCoordinate() + dx;
    int newY = player.getYCoordinate() + dy;

    // Check if the new position is not a wall
    if (map.getTile(newX, newY).getSymbol() != '#') {
        bool enemy_collision = false;

        // Check for collision with enemies
        for (size_t e = 0; e < enemies.size(); e++) {
            if (newY == enemies[e].getYCoordinate() && newX == enemies[e].getXCoordinate()) {
                log_command("You hit the " + enemies[e].getName() + "!");
                enemies[e].setHealth(enemies[e].getHealth() - player.getAttack());
                enemy_collision = true;
                if (enemies[e].getHealth() <= 0) {
                    log_command(enemies[e].getName() + " defeated!");
                    enemies.erase(enemies.begin() + e);
                }
                break;
            }
        }

        // Move player if no enemy collision
        if (!enemy_collision) {
            player.setXCoordinate(newX);
            player.setYCoordinate(newY);
        }
    } else {
        log_command("You can't go that way.");
    }
}

// Place enemies on the map
void Game::placeEnemies() {
    for (int i = 0; i < map.MAX_ENEMIES; i++) {
        int x, y;
        do {
            x = rand() % map.MAP_WIDTH;
            y = rand() % map.MAP_HEIGHT;
        } while (map.getTile(x, y).getSymbol() != '.' || (x == map.getSpawnX() && y == map.getSpawnY()));

        enemies.push_back(Enemy(x, y, "Demon", 'D')); // Add a new enemy
    }
}

// Place items on the map
void Game::placeItems() {
    for (int i = 0; i < map.MAX_ITEMS; i++) {
        int x, y;
        do {
            x = rand() % map.MAP_WIDTH;
            y = rand() % map.MAP_HEIGHT;
        } while (map.getTile(x, y).getSymbol() != '.' || (x == map.getSpawnX() && y == map.getSpawnY()));

        items.push_back(Item(x, y, "Rock", "This is a rock. It is of common value.")); // Add a new item
    }
}

// Move enemies towards the player
void Game::moveEnemies() {
    for (auto& enemy : enemies) {
        // Check if enemy is within the player's FOV
        if (enemy.getXCoordinate() >= player.getXCoordinate() - enemy.getFOVRadius() && 
            enemy.getXCoordinate() <= player.getXCoordinate() + enemy.getFOVRadius() &&
            enemy.getYCoordinate() >= player.getYCoordinate() - enemy.getFOVRadius() && 
            enemy.getYCoordinate() <= player.getYCoordinate() + enemy.getFOVRadius()) {

            int target_x = enemy.getXCoordinate();
            int target_y = enemy.getYCoordinate();

            // Move directly toward the player
            if (target_x < player.getXCoordinate()) {
                target_x++;
            } else if (target_x > player.getXCoordinate()) {
                target_x--;
            }

            if (target_y < player.getYCoordinate()) {
                target_y++;
            } else if (target_y > player.getYCoordinate()) {
                target_y--;
            }

            // Allow for slight deviations occasionally
            if (rand() % 4 == 0) { // 25% chance of a deviation
                if (rand() % 2) target_x += (rand() % 2 ? 1 : -1); // Minor horizontal shift
                if (rand() % 2) target_y += (rand() % 2 ? 1 : -1); // Minor vertical shift
            }

            // Validate next position
            if (target_x >= 0 && target_x < map.MAP_WIDTH && target_y >= 0 && target_y < map.MAP_HEIGHT &&
                map.getTile(target_x, target_y).getSymbol() == '.') {

                // Check for collision with other enemies
                bool occupied = false;
                for (const auto& other_enemy : enemies) {
                    if (&other_enemy != &enemy && 
                        other_enemy.getXCoordinate() == target_x && 
                        other_enemy.getYCoordinate() == target_y) {
                        occupied = true; // Another enemy occupies the target tile
                        break;
                    }
                }

                // Move enemy if target tile is unoccupied
                if (!occupied) {
                    if (target_x == player.getXCoordinate() && target_y == player.getYCoordinate()) {
                        // Enemy attacks the player
                        log_command(enemy.getName() + " attacks you!");
                        player.setHealth(player.getHealth() - enemy.getAttack());
                        if (player.getHealth() <= 0) {
                            log_command("You have been defeated!");
                            break;
                        }
                    } else {
                        enemy.setXCoordinate(target_x);
                        enemy.setYCoordinate(target_y);
                    }
                }
            }
        }
    }
}

// Check for collisions with enemies and items
void Game::checkCollisions() {
    // Check for collisions with enemies
    for (size_t e = 0; e < enemies.size(); e++) {
        if (enemies[e].getXCoordinate() == player.getXCoordinate() &&
            enemies[e].getYCoordinate() == player.getYCoordinate()) {
            log_command("You've been attacked by an enemy!");
            player.setHealth(player.getHealth() - enemies[e].getAttack());

            enemies[e].setHealth(enemies[e].getHealth() - player.getAttack());

            // Check if enemy is defeated
            if (enemies[e].getHealth() <= 0) {
                log_command("Enemy defeated!");
                enemies.erase(enemies.begin() + e);
                e--; // Stay on the same index after removing the enemy
            }
        }
    }

    // Check for collisions with items
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].getXCoordinate() == player.getXCoordinate() && items[i].getYCoordinate() == player.getYCoordinate()) {
            player.addToInventory(items[i]);
            items.erase(items.begin() + i);
            log_command("You picked up an item!");
            break;
        }
    }
}

// Log a command message
void Game::log_command(const std::string &command) {
    if (command_log.size() < ui.LOG_LINES) {
        command_log.push_back(command);
    } else {
        command_log[log_index] = command; // Replace oldest command
    }
    log_index = (log_index + 1) % ui.LOG_LINES; // Update log index
}
