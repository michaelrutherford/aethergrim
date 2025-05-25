// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "log.h"
#include <string>
#include <vector>

class Player {
public:
  // Constants defining the player's field of view radius along X and Y axes
  static const int FOV_X_RADIUS = 5;
  static const int FOV_Y_RADIUS = 4;

  // Default constructor
  Player() {}

  // Singleton instance accessor
  static Player &getInstance() {
    static Player instance;
    return instance;
  }

  // Initialize player attributes and clear inventory
  void initialize();

  // Inventory management: add, remove, or use items
  void addToInventory(Item new_item);
  void removeFromInventory(int index);
  void useItem(int index);

  // Accessor methods
  int getXCoordinate() const;
  int getYCoordinate() const;
  std::string getName() const;
  int getHealth() const;
  int getAttack() const;
  std::vector<Item> getInventory() const;
  Item getItemAt(int index) const;
  int getColor() const;
  char getSymbol() const;

  // Mutator methods
  void setXCoordinate(int new_x);
  void setYCoordinate(int new_y);
  void setName(std::string new_name);
  void setHealth(int new_health);
  void setAttack(int new_attack);
  void setColor(int new_color);
  void setSymbol(char new_symbol);

private:
  // Delete copy constructor and assignment operator
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;

  int x, y;                    // Player's current position on the map
  std::string name;            // Player's display name
  int health;                  // Current health points
  int attack;                  // Attack damage value
  int level;                   // Player's experience level
  int experience;              // Experience points accumulated
  std::vector<Item> inventory; // Items currently held by the player
  int color;                   // Display color code
  char symbol;                 // Character symbol representing the player
};

#endif // PLAYER_H
