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

#include "item.h"

// Default constructor
Item::Item() {
    x = 0;
    y = 0;
    name = "Item";
    color = 6;
    symbol = '$';
}

// Parameterized constructor to create an item with specific attributes
Item::Item(int start_x, int start_y, 
           std::string new_name, std::string new_description) {
    x = start_x;
    y = start_y;
    name = new_name;
    description = new_description;
    color = 6;
    symbol = '$';
}

// Getters
int Item::getXCoordinate() const {
    return x;
}

int Item::getYCoordinate() const {
    return y;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

int Item::getColor() const {
    return color;
}

char Item::getSymbol() const {
    return symbol;
}

// Setters
void Item::setXCoordinate(int new_x) {
    x = new_x;
}

void Item::setYCoordinate(int new_y) {
    y = new_y;
}

void Item::setName(std::string new_name) {
    name = new_name;
}

void Item::setDescription(std::string new_description) {
    description = new_description;
}

void Item::setColor(int new_color) {
    color = new_color;
}

void Item::setSymbol(char new_symbol) {
    symbol = new_symbol;
}
