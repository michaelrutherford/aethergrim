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

#ifndef TILE_H
#define TILE_H

class Tile {
public:
    Tile();
    
    // Getters
    char getSymbol();
    int getColor();
    bool getVisited();
    bool getInFOV();

    // Setters
    void setSymbol(char new_symbol);
    void setColor(int new_color);
    void setVisited(bool new_status);
    void setInFOV(bool new_status);

private:
    char symbol;    // Character representing the tile
    int color;      // Color attribute for display
    bool visited;   // Indicates if the tile has been visited by the player
    bool in_fov;    // Indicates if the tile is within the player's FOV
};

#endif // TILE_H
