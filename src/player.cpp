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

#include "player.h"

// Default constructor
Player::Player()
{
    x = 0;
    y = 0;
    name = "Player";
    health = 100;
    attack = 10;
    level = 1;
    color = 0;
    symbol = '@';
}

// Adds an item to the player's inventory
void Player::addToInventory(Item new_item)
{
    inventory.push_back(new_item);
}

// Getters
int Player::getXCoordinate() const
{
    return x;
}

int Player::getYCoordinate() const
{
    return y;
}

std::string Player::getName() const
{
    return name;
}

int Player::getHealth() const
{
    return health;
}

int Player::getAttack() const
{
    return attack;
}

std::vector<Item> Player::getInventory() const
{
    return inventory;
}

int Player::getColor() const
{
    return color;
}

char Player::getSymbol() const
{
    return symbol;
}

// Setters
void Player::setXCoordinate(int new_x)
{
    x = new_x;
}

void Player::setYCoordinate(int new_y)
{
    y = new_y;
}

void Player::setName(std::string new_name)
{
    name = new_name;
}

void Player::setHealth(int new_health)
{
    health = new_health;
}

void Player::setAttack(int new_attack)
{
    attack = new_attack;
}

void Player::setColor(int new_color)
{
    color = new_color;
}

void Player::setSymbol(char new_symbol)
{
    symbol = new_symbol;
}
