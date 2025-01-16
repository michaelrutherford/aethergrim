// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include "enemy.h"
#include "item.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Map {
public:
    // Constants for map dimensions and room generation
    static const int MAP_WIDTH = 100;
    static const int MAP_HEIGHT = 100;
    static const int MAX_ROOMS = 100;
    static const int ROOM_MIN_SIZE = 5;
    static const int ROOM_MAX_SIZE = 25;
    static const int MAX_ENEMIES = 50;
    static const int MAX_ITEMS = 50;

    // Default constructor
    Map();

    // Field of view functions
    void toggleFOV(int map_x, int map_y);
    void untoggleFOV(int map_x, int map_y);

    // Getters
    Tile getTile(int x, int y) const;
    int getSpawnX();
    int getSpawnY();

private:
    // Structure to represent a room
    struct Room {
        int x;      // X-coordinate of the room's top-left corner
        int y;      // Y-coordinate of the room's top-left corner
        int width;  // Width of the room
        int height; // Height of the room
    };

    // Member variables
    Tile game_map[MAP_HEIGHT][MAP_WIDTH]; // 2D array representing the game map
    std::vector<Room> rooms;               // Vector of rooms

    int spawn_x; // X-coordinate for player spawn point
    int spawn_y; // Y-coordinate for player spawn point
    
    void remove_isolated_walls(); // Remove isolated walls from the map
};

#endif // MAP_H
