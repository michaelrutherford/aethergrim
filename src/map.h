// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef MAP_H
#define MAP_H

#include "enemy.h"
#include "item.h"
#include "player.h"
#include "tile.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

class Map {
public:
  // Constants defining map size, room parameters, and entity limits
  static const int MAP_WIDTH = 100;
  static const int MAP_HEIGHT = 100;
  static const int MAX_ROOMS = 100;
  static const int ROOM_MIN_SIZE = 5;
  static const int ROOM_MAX_SIZE = 25;
  static const int FINAL_ROOM_HEIGHT = 12;
  static const int FINAL_ROOM_WIDTH = 3;
  static const int MAX_ENEMIES = 15;
  static const int MAX_ITEMS = 25;

  // Initialize the map and its contents
  void initialize();

  // Field of view management
  void toggleFOV(int map_x, int map_y);
  void untoggleFOV(int map_x, int map_y);
  void setDepth(int new_depth);

  // Accessor methods
  static Map &getInstance() {       // Singleton instance accessor
    static Map instance;
    return instance;
  }
  Tile getTile(int x, int y) const; // Get tile at coordinates
  int getSpawnX();                  // Get player's spawn X coordinate
  int getSpawnY();                  // Get player's spawn Y coordinate
  int getDepth();                   // Get current map depth
  std::vector<Enemy> &getEnemies(); // Get list of enemies on the map
  std::vector<Item> &getItems();    // Get list of items on the map

private:
  Map();                     // Private constructor (singleton pattern)
  Map(const Map &) = delete; // Disable copy constructor
  Map &operator=(const Map &) = delete; // Disable assignment operator

  // Struct representing a rectangular room within the map
  struct Room {
    int x;      // Top-left X coordinate of the room
    int y;      // Top-left Y coordinate of the room
    int width;  // Room width
    int height; // Room height
  };

  // Internal data members
  Tile game_map[MAP_HEIGHT][MAP_WIDTH]; // 2D grid of tiles representing the map
  std::vector<Room> rooms;              // List of generated rooms

  int spawn_x; // Player's spawn X coordinate
  int spawn_y; // Player's spawn Y coordinate
  int depth;   // Current dungeon/map depth

  // Internal helper methods for map generation and entity placement
  void
  removeIsolatedWalls(); // Remove walls that are not adjacent to floor tiles
  void placeStairs();    // Place staircases on the map
  void placePlayer();    // Place player spawn position
  void placeEnemies();   // Place enemies within rooms
  void placeItems();     // Place items within rooms

  std::vector<Enemy> enemies; // Enemies present in the map
  std::vector<Item> items;    // Items present in the map
};

#endif // MAP_H
