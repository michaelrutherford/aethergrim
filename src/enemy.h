// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
  // Default constructor
  Enemy();

  // Parameterized constructor
  Enemy(int start_x, int start_y, std::string start_name, char start_symbol);

  // Updates the enemy's position
  void moveEnemy(int new_x, int new_y);

  // Accessor methods
  int getXCoordinate() const;
  int getYCoordinate() const;
  std::string getName() const;
  int getHealth() const;
  int getAttack() const;
  int getFOVRadius() const;
  int getColor() const;
  char getSymbol() const;

  // Mutator methods
  void setXCoordinate(int new_x);
  void setYCoordinate(int new_y);
  void setName(std::string new_name);
  void setHealth(int new_health);
  void setAttack(int new_attack);
  void setFOVRadius(int new_radius);
  void setColor(int new_color);
  void setSymbol(char new_symbol);

private:
  int x;            // X-coordinate of the enemy
  int y;            // Y-coordinate of the enemy
  std::string name; // Name of the enemy
  int health;       // Enemy health
  int attack;       // Enemy attack value
  int fov_radius;   // Field of view radius
  int color;        // Color attribute for rendering
  char symbol;      // Symbol representing the enemy
};

#endif // ENEMY_H
