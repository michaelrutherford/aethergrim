// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "game.h"

// Constructor initializes the game state
Game::Game() { reset(); }

void Game::reset() {
  srand(static_cast<unsigned int>(time(NULL))); // Seed srand with current time
  Player::getInstance().initialize();
  Map::getInstance().initialize();
  Log::getInstance().command_log.clear();
  Log::getInstance().log_index = 0;

  // Place player at map's designated spawn position
  Player::getInstance().setXCoordinate(Map::getInstance().getSpawnX());
  Player::getInstance().setYCoordinate(Map::getInstance().getSpawnY());

  Log::getInstance().log_command("Descend the depths. Find the ring.");
  run(); // Start the game loop
}

// Main game loop
void Game::run() {
  ui.drawMenu(main_win); // Display main menu

  clear();
  refresh();

  while (true) {
    resetFOV();        // Update visible tiles
    moveEnemies();     // Update enemy positions
    checkCollisions(); // Resolve any entity collisions

    // Draw game elements to the screen
    ui.drawViewport(viewport_win, Player::getInstance(),
                    Map::getInstance().getEnemies(),
                    Map::getInstance().getItems(), Map::getInstance());
    ui.drawLog(log_win, Log::getInstance(), Log::getInstance().log_index);
    ui.drawInfo(info_win, Player::getInstance());

    // Refresh display windows
    wrefresh(main_win);
    wrefresh(viewport_win);
    wrefresh(log_win);
    wrefresh(info_win);

    // Handle user input
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
    case 'h':
      ui.drawHelp(); // Show help screen
      break;
    case 'i': {
      // Display inventory screen
      WINDOW *inventory_win = newwin(12, 50, (LINES - 12) / 2, (COLS - 50) / 2);
      ui.drawInventory(inventory_win, Player::getInstance());
      delwin(inventory_win);
      break;
    }
    case '>':
      // Attempt to descend to the next floor
      if (Map::getInstance()
              .getTile(Player::getInstance().getXCoordinate(),
                       Player::getInstance().getYCoordinate())
              .getSymbol() == '>') {
        Log::getInstance().log_command("You descend!");
        Map::getInstance().setDepth(Map::getInstance().getDepth() + 1);
        Map::getInstance().initialize();
        Player::getInstance().setXCoordinate(Map::getInstance().getSpawnX());
        Player::getInstance().setYCoordinate(Map::getInstance().getSpawnY());
        clear();
        refresh();
      }
      break;
    case 'q':
      // Show quit screen
      ui.drawQuit();
      clear();
      refresh();
      break;
    }

    // End game if player health is zero or below
    if (Player::getInstance().getHealth() <= 0) {
      Log::getInstance().log_command("Game Over! You have been defeated.");
      ui.drawGameOver(main_win);
      reset(); // Restart the game
    }
  }

  endwin(); // Clean up NCurses
}

// Reset all tiles in the field of view
void Game::resetFOV() {
  for (int y = 0; y < Map::getInstance().MAP_HEIGHT; y++) {
    for (int x = 0; x < Map::getInstance().MAP_WIDTH; x++) {
      Map::getInstance().untoggleFOV(x, y);
    }
  }

  // Reveal tiles around the player based on FOV radius
  for (int dy = -Player::getInstance().FOV_Y_RADIUS;
       dy <= Player::getInstance().FOV_Y_RADIUS; ++dy) {
    for (int dx = -Player::getInstance().FOV_X_RADIUS;
         dx <= Player::getInstance().FOV_X_RADIUS; ++dx) {
      int map_x = Player::getInstance().getXCoordinate() + dx;
      int map_y = Player::getInstance().getYCoordinate() + dy;

      if (map_y >= 0 && map_y < Map::getInstance().MAP_HEIGHT && map_x >= 0 &&
          map_x < Map::getInstance().MAP_WIDTH) {

        if (dx * dx + dy * dy <= Player::getInstance().FOV_X_RADIUS *
                                     Player::getInstance().FOV_X_RADIUS) {
          Map::getInstance().toggleFOV(map_x, map_y);
        }
      }
    }
  }
}

// Attempt to move the player by dx, dy
void Game::movePlayer(int dx, int dy) {
  int newX = Player::getInstance().getXCoordinate() + dx;
  int newY = Player::getInstance().getYCoordinate() + dy;

  // Check if destination tile is walkable
  if (Map::getInstance().getTile(newX, newY).getPassable()) {
    bool enemy_collision = false;

    // Check for and resolve enemy collisions
    for (size_t e = 0; e < Map::getInstance().getEnemies().size(); e++) {
      if (newY == Map::getInstance().getEnemies()[e].getYCoordinate() &&
          newX == Map::getInstance().getEnemies()[e].getXCoordinate()) {
        Log::getInstance().log_command(
            "You hit the " + Map::getInstance().getEnemies()[e].getName() +
            "!");
        Map::getInstance().getEnemies()[e].setHealth(
            Map::getInstance().getEnemies()[e].getHealth() -
            Player::getInstance().getAttack());
        enemy_collision = true;
        if (Map::getInstance().getEnemies()[e].getHealth() <= 0) {
          Log::getInstance().log_command(
              Map::getInstance().getEnemies()[e].getName() + " defeated!");
          Map::getInstance().getEnemies().erase(
              Map::getInstance().getEnemies().begin() + e);
        }
        break;
      }
    }

    if (!enemy_collision) {
      Player::getInstance().setXCoordinate(newX);
      Player::getInstance().setYCoordinate(newY);
    }
  } else {
    Log::getInstance().log_command("You can't go that way.");
  }
}

// Move enemies toward the player if within field of view
void Game::moveEnemies() {
  for (auto &enemy : Map::getInstance().getEnemies()) {
    if (enemy.getXCoordinate() >=
            Player::getInstance().getXCoordinate() - enemy.getFOVRadius() &&
        enemy.getXCoordinate() <=
            Player::getInstance().getXCoordinate() + enemy.getFOVRadius() &&
        enemy.getYCoordinate() >=
            Player::getInstance().getYCoordinate() - enemy.getFOVRadius() &&
        enemy.getYCoordinate() <=
            Player::getInstance().getYCoordinate() + enemy.getFOVRadius()) {

      int target_x = enemy.getXCoordinate();
      int target_y = enemy.getYCoordinate();

      // Move one step closer to the player
      if (target_x < Player::getInstance().getXCoordinate())
        target_x++;
      else if (target_x > Player::getInstance().getXCoordinate())
        target_x--;

      if (target_y < Player::getInstance().getYCoordinate())
        target_y++;
      else if (target_y > Player::getInstance().getYCoordinate())
        target_y--;

      // Add randomness to movement
      if (rand() % 4 == 0) {
        if (rand() % 2)
          target_x += (rand() % 2 ? 1 : -1);
        if (rand() % 2)
          target_y += (rand() % 2 ? 1 : -1);
      }

      // Check for valid tile and avoid overlap
      if (target_x >= 0 && target_x < Map::getInstance().MAP_WIDTH &&
          target_y >= 0 && target_y < Map::getInstance().MAP_HEIGHT &&
          Map::getInstance().getTile(target_x, target_y).getSymbol() == '.') {

        bool occupied = false;
        for (const auto &other_enemy : Map::getInstance().getEnemies()) {
          if (&other_enemy != &enemy &&
              other_enemy.getXCoordinate() == target_x &&
              other_enemy.getYCoordinate() == target_y) {
            occupied = true;
            break;
          }
        }

        if (!occupied) {
          // Attack player if adjacent
          if (target_x == Player::getInstance().getXCoordinate() &&
              target_y == Player::getInstance().getYCoordinate()) {
            Log::getInstance().log_command(enemy.getName() + " attacks you!");
            Player::getInstance().setHealth(Player::getInstance().getHealth() -
                                            enemy.getAttack());

            if (Player::getInstance().getHealth() <= 0) {
              Log::getInstance().log_command("You have been defeated!");
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

// Handle player collisions with enemies and items
void Game::checkCollisions() {
  // Enemy collisions
  for (size_t e = 0; e < Map::getInstance().getEnemies().size(); e++) {
    if (Map::getInstance().getEnemies()[e].getXCoordinate() ==
            Player::getInstance().getXCoordinate() &&
        Map::getInstance().getEnemies()[e].getYCoordinate() ==
            Player::getInstance().getYCoordinate()) {

      Log::getInstance().log_command(
          "You've been attacked by a " +
          Map::getInstance().getEnemies()[e].getName() + "!");
      Player::getInstance().setHealth(
          Player::getInstance().getHealth() -
          Map::getInstance().getEnemies()[e].getAttack());
      Map::getInstance().getEnemies()[e].setHealth(
          Map::getInstance().getEnemies()[e].getHealth() -
          Player::getInstance().getAttack());

      if (Map::getInstance().getEnemies()[e].getHealth() <= 0) {
        Log::getInstance().log_command(
            Map::getInstance().getEnemies()[e].getName() + " defeated!");
        Map::getInstance().getEnemies().erase(
            Map::getInstance().getEnemies().begin() + e);
        e--; // Adjust index after removal
      }
    }
  }

  // Item pickups
  for (size_t i = 0; i < Map::getInstance().getItems().size(); i++) {
    if (Map::getInstance().getItems()[i].getXCoordinate() ==
            Player::getInstance().getXCoordinate() &&
        Map::getInstance().getItems()[i].getYCoordinate() ==
            Player::getInstance().getYCoordinate()) {

      if (Map::getInstance().getItems()[i].getName() == "Health Potion") {
        Player::getInstance().addToInventory(Map::getInstance().getItems()[i]);
        Log::getInstance().log_command(
            "You picked up a " + Map::getInstance().getItems()[i].getName() +
            ".");
        Map::getInstance().getItems().erase(
            Map::getInstance().getItems().begin() + i);
        break;
      } else {
        // Game over on picking up non-healing item
        ui.drawGameOver(main_win);
        Map::getInstance().setDepth(1);
        reset();
      }
    }
  }
}
