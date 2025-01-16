// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "tile.h"

// Default constructor
Tile::Tile()
{
    symbol = ' ';
    color = 0;
    visited = false;
    in_fov = false;
}

// Getters
char Tile::getSymbol()
{
    return symbol;
}

int Tile::getColor()
{
    return color;
}

bool Tile::getVisited()
{
    return visited;
}

bool Tile::getInFOV()
{
    return in_fov;
}

// Setters
void Tile::setSymbol(char new_symbol)
{
    symbol = new_symbol;
}

void Tile::setColor(int new_color)
{
    color = new_color;
}

void Tile::setVisited(bool new_status)
{
    visited = new_status;
}

void Tile::setInFOV(bool new_status)
{
    in_fov = new_status;
}
