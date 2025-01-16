// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "item.h"

class Player {
public:
    // Constants defining the field of view (FOV) radius
    static const int FOV_X_RADIUS = 5; 
    static const int FOV_Y_RADIUS = 4;

    // Default constructor
    Player();
    
    // Method to add an item to the player's inventory
    void addToInventory(Item new_item);

    // Getters
    int getXCoordinate() const;
    int getYCoordinate() const;
    std::string getName() const;
    int getHealth() const;
    int getAttack() const;
    std::vector<Item> getInventory() const;
    int getColor() const;
    char getSymbol() const;

    // Setters
    void setXCoordinate(int new_x);
    void setYCoordinate(int new_y);
    void setName(std::string new_name);
    void setHealth(int new_health);
    void setAttack(int new_attack);
    void setColor(int new_color);
    void setSymbol(char new_symbol);

private:
    int x, y;                           // Player's position on the map
    std::string name;                   // Player's name
    int health;                         // Player's health points
    int attack;                         // Player's attack power
    int level;                          // Player's level
    int experience;                     // Player's experience points
    std::vector<Item> inventory;        // Player's inventory of items
    int color;                          // Color attribute for display
    char symbol;                        // Symbol representing the player
};

#endif // PLAYER_H
