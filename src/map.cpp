// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "map.h"

// Default constructor
Map::Map() { setDepth(1); }

// Initialize the map by seeding srand, clearing existing data, and generating
// rooms
void Map::initialize() {
  srand(static_cast<unsigned int>(
      time(NULL))); // Seed the random number generator

  // Clear existing rooms, enemies, and items
  rooms.clear();
  enemies.clear();
  items.clear();

  // Fill the entire map with wall tiles and set their properties
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      game_map[y][x].setSymbol('#');
      game_map[y][x].setColor(1);
      game_map[y][x].setPassable(false);
      game_map[y][x].setInFOV(false);
      game_map[y][x].setVisited(false);
    }
  }

  if (depth <= 3) {
    // Generate multiple random rooms
    for (int i = 0; i < MAX_ROOMS; i++) {
      int width = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
      int height = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
      int x = rand() % (MAP_WIDTH - width - 2) +
              1; // Random X position inside map bounds
      int y = rand() % (MAP_HEIGHT - height - 2) +
              1; // Random Y position inside map bounds

      Room new_room = {x, y, width, height}; // Define new room
      bool collision = false;

      // Check for overlap with existing rooms
      for (const auto &room : rooms) {
        if (!(new_room.x + new_room.width < room.x ||
              new_room.x > room.x + room.width ||
              new_room.y + new_room.height < room.y ||
              new_room.y > room.y + room.height)) {
          collision = true; // Overlap detected
          break;
        }
      }

      if (!collision) {
        // Carve out the room by placing floor tiles
        for (int y_offset = 0; y_offset < height; y_offset++) {
          for (int x_offset = 0; x_offset < width; x_offset++) {
            game_map[y + y_offset][x + x_offset].setSymbol('.');
            game_map[y + y_offset][x + x_offset].setColor(2);
            game_map[y + y_offset][x + x_offset].setPassable(true);
          }
        }
        rooms.push_back(new_room); // Add room to the list

        // Connect this room to the previous room with a hallway
        if (rooms.size() > 1) {
          int prev_x =
              rooms[rooms.size() - 2].x + rooms[rooms.size() - 2].width / 2;
          int prev_y =
              rooms[rooms.size() - 2].y + rooms[rooms.size() - 2].height / 2;
          int new_x = new_room.x + new_room.width / 2;
          int new_y = new_room.y + new_room.height / 2;

          // Randomly decide hallway direction: horizontal first or vertical
          // first
          if (rand() % 2) {
            // Horizontal corridor, then vertical
            for (int x = std::min(prev_x, new_x); x <= std::max(prev_x, new_x);
                 x++) {
              game_map[prev_y][x].setSymbol('.');
              game_map[prev_y][x].setColor(2);
              game_map[prev_y][x].setPassable(true);
            }
            for (int y = std::min(prev_y, new_y); y <= std::max(prev_y, new_y);
                 y++) {
              game_map[y][new_x].setSymbol('.');
              game_map[y][new_x].setColor(2);
              game_map[y][new_x].setPassable(true);
            }
          } else {
            // Vertical corridor, then horizontal
            for (int y = std::min(prev_y, new_y); y <= std::max(prev_y, new_y);
                 y++) {
              game_map[y][prev_x].setSymbol('.');
              game_map[y][prev_x].setColor(2);
              game_map[y][prev_x].setPassable(true);
            }
            for (int x = std::min(prev_x, new_x); x <= std::max(prev_x, new_x);
                 x++) {
              game_map[new_y][x].setSymbol('.');
              game_map[new_y][x].setColor(2);
              game_map[new_y][x].setPassable(true);
            }
          }
        }
      }
    }

    // Remove wall tiles that have no adjacent floor tiles to open up the map
    removeIsolatedWalls();

    // Place stairs, player, enemies, and items
    placeStairs();
    placePlayer();
    placeEnemies();
    placeItems();
  } else {
    // For depths greater than 3, generate a single final room in the center
    int x = MAP_WIDTH / 2;
    int y = MAP_HEIGHT / 2;
    Room new_room = {x, y, FINAL_ROOM_WIDTH, FINAL_ROOM_HEIGHT};

    // Carve out the final room floor tiles
    for (int y_offset = 0; y_offset < FINAL_ROOM_HEIGHT; y_offset++) {
      for (int x_offset = 0; x_offset < FINAL_ROOM_WIDTH; x_offset++) {
        game_map[y + y_offset][x + x_offset].setSymbol('.');
        game_map[y + y_offset][x + x_offset].setColor(2);
        game_map[y + y_offset][x + x_offset].setPassable(true);
      }
    }
    rooms.push_back(new_room);

    // Remove isolated walls around the final room
    removeIsolatedWalls();

    // Add a special item ("Ring") in the final room
    items.push_back(Item(rooms[0].x + rooms[0].width / 2,
                         rooms[0].y + rooms[0].height - FINAL_ROOM_HEIGHT,
                         "Ring", "This is the Ring.", 'o'));

    // Place the player in the final room
    placePlayer();
  }
}

// Remove wall tiles that are isolated (no adjacent floor tiles)
void Map::removeIsolatedWalls() {
  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      // If tile is a wall and none of the adjacent 8 tiles are floors, remove
      // it
      if (game_map[y][x].getSymbol() == '#' &&
          !(game_map[y - 1][x].getSymbol() == '.' ||
            game_map[y + 1][x].getSymbol() == '.' ||
            game_map[y][x - 1].getSymbol() == '.' ||
            game_map[y][x + 1].getSymbol() == '.' ||
            game_map[y - 1][x - 1].getSymbol() == '.' ||
            game_map[y - 1][x + 1].getSymbol() == '.' ||
            game_map[y + 1][x - 1].getSymbol() == '.' ||
            game_map[y + 1][x + 1].getSymbol() == '.')) {
        game_map[y][x].setSymbol(' '); // Remove isolated wall tile
      }
    }
  }
}

// Randomly place stairs in three different rooms
void Map::placeStairs() {
  int random_room = 0;
  int x, y;
  for (int i = 0; i < 3; i++) {
    random_room = (rand() % (rooms.size() - 1)) +
                  1; // Choose a random room (not the first)
    x = rooms[random_room].x + rooms[random_room].width / 2;
    y = rooms[random_room].y + rooms[random_room].height / 2;
    game_map[y][x].setSymbol('>'); // Place stairs symbol
  }
}

// Set player's spawn point in the map based on depth
void Map::placePlayer() {
  if (depth < 3) {
    // Spawn player in the center of the first room for early depths
    spawn_x = rooms[0].x + rooms[0].width / 2;
    spawn_y = rooms[0].y + rooms[0].height / 2;
  } else {
    // Spawn player near the bottom center of the first room at deeper levels
    spawn_x = rooms[0].x + rooms[0].width / 2;
    spawn_y = rooms[0].y + rooms[0].height - 1;
  }
}

// Spawn enemies randomly within rooms (excluding the first room)
void Map::placeEnemies() {
  int random_room = 0;
  int x, y;
  for (int i = 0; i < Map::getInstance().MAX_ENEMIES; i++) {
    random_room =
        (rand() % (rooms.size() - 1)) + 1; // Random room index after the first
    x = rooms[random_room].x + (rand() % (rooms[random_room].width - 1));
    y = rooms[random_room].y + (rand() % (rooms[random_room].height - 1));
    enemies.push_back(
        Enemy(x, y, "Ghost", 'G')); // Add a ghost enemy at random position
  }
}

// Spawn items randomly within rooms (excluding the first room)
void Map::placeItems() {
  int random_room = 0;
  int x, y;
  for (int i = 0; i < Map::getInstance().MAX_ITEMS; i++) {
    random_room = (rand() % (rooms.size() - 1)) + 1;
    x = rooms[random_room].x + (rand() % (rooms[random_room].width - 1));
    y = rooms[random_room].y + (rand() % (rooms[random_room].height - 1));
    items.push_back(Item(x, y, "Health Potion",
                         "Drinking this potion will restore health.",
                         '!')); // Add a health potion item
  }
}

// Return the tile at specified (x, y) coordinates
Tile Map::getTile(int x, int y) const { return game_map[y][x]; }

// Get current map depth
int Map::getDepth() { return depth; }

// Get player's spawn X coordinate
int Map::getSpawnX() { return spawn_x; }

// Get player's spawn Y coordinate
int Map::getSpawnY() { return spawn_y; }

// Get the list of enemies on the map
std::vector<Enemy> &Map::getEnemies() { return enemies; }

// Get the list of items on the map
std::vector<Item> &Map::getItems() { return items; }

// Mark a tile as visible and visited in the player's field of view
void Map::toggleFOV(int map_x, int map_y) {
  game_map[map_y][map_x].setInFOV(true);
  game_map[map_y][map_x].setVisited(true);
}

// Mark a tile as not currently visible in the player's field of view
void Map::untoggleFOV(int map_x, int map_y) {
  game_map[map_y][map_x].setInFOV(false);
}

// Update the map's depth value
void Map::setDepth(int new_depth) { depth = new_depth; }
