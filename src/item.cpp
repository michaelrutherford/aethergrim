// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "item.h"

// Default constructor
Item::Item()
{
    x = 0;
    y = 0;
    name = "Item";
    color = 6;
    symbol = '$';
}

// Parameterized constructor to create an item with specific attributes
Item::Item(int start_x, int start_y, 
           std::string new_name, std::string new_description)
{
    x = start_x;
    y = start_y;
    name = new_name;
    description = new_description;
    color = 6;
    symbol = '$';
}

// Getters
int Item::getXCoordinate() const
{
    return x;
}

int Item::getYCoordinate() const
{
    return y;
}

std::string Item::getName() const
{
    return name;
}

std::string Item::getDescription() const
{
    return description;
}

int Item::getColor() const
{
    return color;
}

char Item::getSymbol() const
{
    return symbol;
}

// Setters
void Item::setXCoordinate(int new_x)
{
    x = new_x;
}

void Item::setYCoordinate(int new_y)
{
    y = new_y;
}

void Item::setName(std::string new_name)
{
    name = new_name;
}

void Item::setDescription(std::string new_description)
{
    description = new_description;
}

void Item::setColor(int new_color)
{
    color = new_color;
}

void Item::setSymbol(char new_symbol)
{
    symbol = new_symbol;
}
