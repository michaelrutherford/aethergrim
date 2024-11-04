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

#include "enemy.h"

// Default constructor
Enemy::Enemy() {
    x = 0;
    y = 0;
    name = "Enemy";
    health = 20;
    attack = 10;
    fov_radius = 5;
    color = 7;
    symbol = 'E';
}

// Constructor for the Enemy class with specified starting values
Enemy::Enemy(int start_x, int start_y, std::string start_name, char start_symbol) {
    x = start_x;
    y = start_y;
    name = start_name;
    health = 20;
    attack = 1;
    fov_radius = 5;
    color = 7;
    symbol = start_symbol;
}

// Method to move the enemy to a new position
void Enemy::moveEnemy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

// Getters
int Enemy::getXCoordinate() const {
    return x;
}

int Enemy::getYCoordinate() const {
    return y;
}

std::string Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getAttack() const {
    return attack;
}

int Enemy::getFOVRadius() const {
    return fov_radius;
}

int Enemy::getColor() const {
    return color;
}

char Enemy::getSymbol() const {
    return symbol;
}

// Setters
void Enemy::setXCoordinate(int new_x) {
    x = new_x;
}

void Enemy::setYCoordinate(int new_y) {
    y = new_y;
}

void Enemy::setHealth(int new_health) {
    health = new_health;
}

void Enemy::setAttack(int new_attack) {
    attack = new_attack;
}

void Enemy::setFOVRadius(int new_radius) {
    fov_radius = new_radius;
}

void Enemy::setColor(int new_color) {
    color = new_color;
}

void Enemy::setSymbol(char new_symbol) {
    symbol = new_symbol;
}
