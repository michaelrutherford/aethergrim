// MIT License
// Copyright (c) 2024- Michael Rutherford

#ifndef TILE_H
#define TILE_H

class Tile {
public:
  Tile();

  // Accessor methods
  char getSymbol();
  int getColor();
  bool getVisited();
  bool getInFOV();
  bool getPassable();

  // Mutator methods
  void setSymbol(char new_symbol);
  void setColor(int new_color);
  void setVisited(bool new_status);
  void setInFOV(bool new_status);
  void setPassable(bool new_passable);

private:
  char symbol;   // Character representing the tile
  int color;     // Color attribute for display
  bool visited;  // Indicates if the tile has been visited by the player
  bool in_fov;   // Indicates if the tile is within the player's FOV
  bool passable; // Indicates if the tile can be moved through
};

#endif // TILE_H
