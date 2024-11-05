/* 
* Grumacetus
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

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    // Default constructor
    Enemy();
    
    // Parameterized constructor for custom initialization
    Enemy(int start_x, int start_y, std::string start_name, char start_symbol);
    
    // Method to move the enemy to a new position
    void moveEnemy(int new_x, int new_y);

    // Getters
    int getXCoordinate() const;
    int getYCoordinate() const;
    std::string getName() const;
    int getHealth() const;
    int getAttack() const;
    int getFOVRadius() const;
    int getColor() const;
    char getSymbol() const;

    // Setters
    void setXCoordinate(int new_x);
    void setYCoordinate(int new_y);
    void setName(std::string new_name);
    void setHealth(int new_health);
    void setAttack(int new_attack);
    void setFOVRadius(int new_radius);
    void setColor(int new_color);
    void setSymbol(char new_symbol);

private:
    int x;                // x-coordinate of the enemy
    int y;                // y-coordinate of the enemy
    std::string name;     // Name of the enemy
    int health;           // Enemy health
    int attack;           // Enemy attack value
    int fov_radius;       // Field of view radius
    int color;            // Color attribute for rendering
    char symbol;          // Symbol representing the enemy
};

#endif // ENEMY_H
