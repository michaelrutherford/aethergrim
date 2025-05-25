// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "enemy.h"

// Default constructor
Enemy::Enemy() {
  x = 0;
  y = 0;
  name = "Enemy";
  health = 30;
  attack = 10;
  fov_radius = 5;
  color = 7;
  symbol = 'E';
}

// Parameterized constructor
Enemy::Enemy(int start_x, int start_y, std::string start_name,
             char start_symbol) {
  x = start_x;
  y = start_y;
  name = start_name;
  health = 30;
  attack = 2;
  fov_radius = 5;
  color = 7;
  symbol = start_symbol;
}

// Updates the enemy's position
void Enemy::moveEnemy(int new_x, int new_y) {
  x = new_x;
  y = new_y;
}

// Accessor methods
int Enemy::getXCoordinate() const { return x; }

int Enemy::getYCoordinate() const { return y; }

std::string Enemy::getName() const { return name; }

int Enemy::getHealth() const { return health; }

int Enemy::getAttack() const { return attack; }

int Enemy::getFOVRadius() const { return fov_radius; }

int Enemy::getColor() const { return color; }

char Enemy::getSymbol() const { return symbol; }

// Mutator methods
void Enemy::setXCoordinate(int new_x) { x = new_x; }

void Enemy::setYCoordinate(int new_y) { y = new_y; }

void Enemy::setHealth(int new_health) { health = new_health; }

void Enemy::setAttack(int new_attack) { attack = new_attack; }

void Enemy::setFOVRadius(int new_radius) { fov_radius = new_radius; }

void Enemy::setColor(int new_color) { color = new_color; }

void Enemy::setSymbol(char new_symbol) { symbol = new_symbol; }
