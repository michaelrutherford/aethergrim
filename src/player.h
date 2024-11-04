/* 
* Sunken Ruins of Grumacetus
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
