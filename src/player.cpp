// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "player.h"

// Initialize player attributes and clear inventory
void Player::initialize() {
  x = 0;
  y = 0;
  name = "Player";
  health = 30;
  attack = 8;
  level = 1;
  color = 0;
  symbol = '@';
  inventory.clear();
}

// Add an item to the player's inventory
void Player::addToInventory(Item new_item) { inventory.push_back(new_item); }

// Remove an item from the player's inventory by index
void Player::removeFromInventory(int index) {
  inventory.erase(inventory.begin() + index);
}

// Use an item from the inventory at the given index and remove it
void Player::useItem(int index) {
  Item item = getItemAt(index);
  Log::getInstance().log_command("You used a " + item.getName() + "!");

  inventory.erase(inventory.begin() + index);

  // Heal the player by 10, not exceeding max health of 30
  if ((health + 10) > 30) {
    health = 30;
  } else {
    health += 10;
  }
}

// Accessor methods
int Player::getXCoordinate() const { return x; }

int Player::getYCoordinate() const { return y; }

std::string Player::getName() const { return name; }

int Player::getHealth() const { return health; }

int Player::getAttack() const { return attack; }

std::vector<Item> Player::getInventory() const { return inventory; }

Item Player::getItemAt(int index) const { return inventory[index]; }

int Player::getColor() const { return color; }

char Player::getSymbol() const { return symbol; }

// Mutator methods
void Player::setXCoordinate(int new_x) { x = new_x; }

void Player::setYCoordinate(int new_y) { y = new_y; }

void Player::setName(std::string new_name) { name = new_name; }

void Player::setHealth(int new_health) { health = new_health; }

void Player::setAttack(int new_attack) { attack = new_attack; }

void Player::setColor(int new_color) { color = new_color; }

void Player::setSymbol(char new_symbol) { symbol = new_symbol; }
