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

#include "map.h"

// Default constructor
Map::Map() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed random number gen

    // Initialize the map with walls and the wall color
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game_map[y][x].setSymbol('#');
            game_map[y][x].setColor(1);
        }
    }

    // Generate rooms
    for (int i = 0; i < MAX_ROOMS; i++) {
        int width = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        int height = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        int x = rand() % (MAP_WIDTH - width - 2) + 1; // Random x position
        int y = rand() % (MAP_HEIGHT - height - 2) + 1; // Random y position

        Room new_room = {x, y, width, height}; // Create new room
        bool collision = false;

        // Check for collisions with existing rooms
        for (const auto& room : rooms) {
            if (!(new_room.x + new_room.width < room.x || 
                  new_room.x > room.x + room.width || 
                  new_room.y + new_room.height < room.y || 
                  new_room.y > room.y + room.height)) {
                collision = true; // Collision detected
                break;
            }
        }

        if (!collision) {
            // Place the room in the map
            for (int y_offset = 0; y_offset < height; y_offset++) {
                for (int x_offset = 0; x_offset < width; x_offset++) {
                    // Set tile with floor and floor color
                    game_map[y + y_offset][x + x_offset].setSymbol('.');
                    game_map[y + y_offset][x + x_offset].setColor(2);
                }
            }
            rooms.push_back(new_room); // Add the new room to the list

            // Connect to the previous room if there are multiple rooms
            if (rooms.size() > 1) {
                int prev_x = rooms[rooms.size() - 2].x + rooms[rooms.size() - 2].width / 2;
                int prev_y = rooms[rooms.size() - 2].y + rooms[rooms.size() - 2].height / 2;
                int new_x = new_room.x + new_room.width / 2;
                int new_y = new_room.y + new_room.height / 2;

                // Create a hallway between the two rooms
                if (rand() % 2) {
                    // Horizontal first, then vertical
                    for (int x = std::min(prev_x, new_x); x <= std::max(prev_x, new_x); x++) {
                        game_map[prev_y][x].setSymbol('.');
                        game_map[prev_y][x].setColor(2);
                    }
                    for (int y = std::min(prev_y, new_y); y <= std::max(prev_y, new_y); y++) {
                        game_map[y][new_x].setSymbol('.');
                        game_map[y][new_x].setColor(2);
                    }
                } else {
                    // Vertical first, then horizontal
                    for (int y = std::min(prev_y, new_y); y <= std::max(prev_y, new_y); y++) {
                        game_map[y][prev_x].setSymbol('.');
                        game_map[y][prev_x].setColor(2);
                    }
                    for (int x = std::min(prev_x, new_x); x <= std::max(prev_x, new_x); x++) {
                        game_map[new_y][x].setSymbol('.');
                        game_map[new_y][x].setColor(2);
                    }
                }
            }
        }
    }

    // Remove isolated walls to create a more open map
    remove_isolated_walls();
    
    // Set the player's spawn point to the center of the first room
    spawn_x = rooms[0].x + rooms[0].width / 2;
    spawn_y = rooms[0].y + rooms[0].height / 2;
}

// Remove walls that are isolated and not adjacent to any floor tiles
void Map::remove_isolated_walls() {
    for (int y = 1; y < MAP_HEIGHT - 1; y++) {
        for (int x = 1; x < MAP_WIDTH - 1; x++) {
            // If the tile is a wall and has no adjacent floor tiles, remove it
            if (game_map[y][x].getSymbol() == '#' && 
                !(game_map[y-1][x].getSymbol() == '.' || game_map[y+1][x].getSymbol() == '.' || 
                  game_map[y][x-1].getSymbol() == '.' || game_map[y][x+1].getSymbol() == '.' ||
                  game_map[y-1][x-1].getSymbol() == '.' || game_map[y-1][x+1].getSymbol() == '.' ||
                  game_map[y+1][x-1].getSymbol() == '.' || game_map[y+1][x+1].getSymbol() == '.')) {
                game_map[y][x].setSymbol(' '); // Remove the isolated wall
            }
        }
    }
}

// Get the tile at the specified coordinates
Tile Map::getTile(int x, int y) const {
    return game_map[y][x]; // Return the tile object
}

// Get the x-coordinate of where to spawn the player
int Map::getSpawnX() {
    return spawn_x;
}

// Get the y-coordinate of where to spawn the player
int Map::getSpawnY() {
    return spawn_y;
}

// Set the field of view status for a tile
void Map::toggleFOV(int map_x, int map_y) {
    game_map[map_y][map_x].setInFOV(true); // Mark tile as in FOV
    game_map[map_y][map_x].setVisited(true); // Mark tile as visited
}

// Reset the field of view status for a tile
void Map::untoggleFOV(int map_x, int map_y) {
    game_map[map_y][map_x].setInFOV(false); // Unmark tile from FOV
}
