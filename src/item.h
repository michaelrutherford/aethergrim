/* 
* Aethergrim
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

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    // Default constructor
    Item();

    // Parameterized constructor for creating an item with specific attributes
    Item(int x, int y, std::string new_name, std::string new_description);
    
    // Getter methods
    int getXCoordinate() const;
    int getYCoordinate() const;
    std::string getName() const;
    std::string getDescription() const;
    int getColor() const;
    char getSymbol() const;

    // Setter methods
    void setXCoordinate(int new_x);
    void setYCoordinate(int new_y);
    void setName(std::string new_name);
    void setDescription(std::string new_description);
    void setColor(int new_color);
    void setSymbol(char new_symbol);

private:
    int x;                              // X-coordinate of the item
    int y;                              // Y-coordinate of the item
    std::string name;                   // Name of the item
    std::string description;            // Description of the item
    char symbol;                        // Symbol representing the item
    int color;                          // Color code for the item
};

#endif // ITEM_H
