// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
  // Default constructor
  Item();

  // Parameterized constructor
  Item(int x, int y, std::string new_name, std::string new_description,
       char new_symbol);

  // Accessor methods
  int getXCoordinate() const;
  int getYCoordinate() const;
  std::string getName() const;
  std::string getDescription() const;
  int getColor() const;
  char getSymbol() const;

  // Mutator methods
  void setXCoordinate(int new_x);
  void setYCoordinate(int new_y);
  void setName(std::string new_name);
  void setDescription(std::string new_description);
  void setColor(int new_color);
  void setSymbol(char new_symbol);

private:
  int x;                   // X-coordinate of the item
  int y;                   // Y-coordinate of the item
  std::string name;        // Name of the item
  std::string description; // Description of the item
  char symbol;             // Symbol representing the item
  int color;               // Color code for the item
};

#endif // ITEM_H
