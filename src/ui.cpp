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

#include "ui.h"

// Default constructor
UI::UI() {
    initialize();
}

// Destructor to clean up
UI::~UI() {
    endwin();
}

// Initializes the NCurses window and settings
void UI::initialize() {
    initscr();            // Start NCurses mode
    cbreak();             // Disable line buffering
    noecho();             // Don't echo user input
    keypad(stdscr, TRUE); // Enable special keys (like arrows)
    curs_set(0);          // Hide the cursor
    start_color();        // Enable color functionality
    setupColors();        // Set up color pairs
}

// Setup color pairs for use in the UI
void UI::setupColors() {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);     // Wall color
    init_pair(2, COLOR_GREEN, COLOR_BLACK);    // Ground color
    init_pair(3, COLOR_WHITE, COLOR_BLACK);    // Visited tiles color
    init_pair(4, COLOR_BLACK, COLOR_BLACK);    // Unvisited tiles color
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);  // Info color
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);   // Item color
    init_pair(7, COLOR_RED, COLOR_BLACK);      // Enemy color
}

// Prints text word-wrapped in the given window
void UI::wrapPrint(WINDOW *win, const std::string &text, int start_y, int start_x, int width) {
    std::istringstream words(text);
    std::string word;
    int current_y = start_y;
    int current_x = start_x;

    while (words >> word) {
        if (current_x + static_cast<int>(word.length()) + 1 > width) {
            current_y++;
            current_x = start_x;
        }
        mvwprintw(win, current_y, current_x, "%s ", word.c_str());
        current_x += static_cast<int>(word.length()) + 1;
    }
}

// Displays the main menu and handles user input
void UI::drawMenu(WINDOW *win) {
    werase(win);
    box(win, 0, 0);

    mvwprintw(win, 2, COLS / 2 - 30, 
            "    ___       _   _                         _");
    mvwprintw(win, 3, COLS / 2 - 30, 
            "   / _ \\     | | | |                       (_)");
    mvwprintw(win, 4, COLS / 2 - 30, 
            "  / /_\\ \\ ___| |_| |__   ___ _ __ __ _ _ __ _ _ __ ___");
    mvwprintw(win, 5, COLS / 2 - 30, 
            "  |  _  |/ _ \\ __| '_ \\ / _ \\ '__/ _` | '__| | '_ ` _ \\");
    mvwprintw(win, 6, COLS / 2 - 30, 
            "  | | | |  __/ |_| | | |  __/ | | (_| | |  | | | | | | |");
    mvwprintw(win, 7, COLS / 2 - 30, 
            "  \\_| |_/\\___|\\__|_| |_|\\___|_|  \\__, |_|  |_|_| |_| |_|");
    mvwprintw(win, 8, COLS / 2 - 30, 
            "                                  __/ |");
    mvwprintw(win, 9, COLS / 2 - 30, 
            "                                 |___/   ");
    
    const std::vector<std::string> options = {"New Game", "About", "Help", "Quit"};
    size_t selected_item = 0;
    int ch;

    // Main loop for displaying the menu
    while (true) {
        werase(win);
        box(win, 0, 0);

        // Highlight selected menu option
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == selected_item) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, (LINES / 2) + i - (options.size() / 2), COLS / 2 - 7, "%s", options[i].c_str());
            wattroff(win, A_REVERSE);
        }

        wrefresh(win); // Refresh to show options

        // Handle user input
        ch = wgetch(win);
        if (ch == KEY_UP && selected_item > 0) {
            selected_item--; // Move selection up
        } else if (ch == KEY_DOWN && selected_item < options.size() - 1) {
            selected_item++; // Move selection down
        } else if (ch == KEY_ENTER || ch == '\n') { // Enter key
            switch (selected_item) {
                case 0: return;            // New Game
                case 1: break;             // About
                case 2: break;             // Help
                case 3: endwin(); exit(0); // Quit
            }
        }
    }
}

// Draws the game viewport centered around the player
void UI::drawViewport(WINDOW *win, const Player &player, const std::vector<Enemy> &enemies, const std::vector<Item> &items, const Map &map) {
    int playerX = player.getXCoordinate();
    int playerY = player.getYCoordinate();

    for (int y = 0; y < VIEWPORT_HEIGHT; y++) {
        for (int x = 0; x < VIEWPORT_WIDTH; x++) {
            int map_x = playerX - VIEWPORT_WIDTH / 2 + x;
            int map_y = playerY - VIEWPORT_HEIGHT / 2 + y;

            char ch = ' ';
            int color_pair = 4;

            // Check if within map boundaries
            if (map_y >= 0 && map_y < map.MAP_HEIGHT && map_x >= 0 && map_x < map.MAP_WIDTH) {
                // Check if the tile is in FOV
                if (map.getTile(map_x, map_y).getInFOV()) {
                    ch = map.getTile(map_x, map_y).getSymbol();
                    color_pair = map.getTile(map_x, map_y).getColor();

                    // Check for enemies
                    for (const auto& enemy : enemies) {
                        if (enemy.getXCoordinate() == map_x && enemy.getYCoordinate() == map_y) {
                            ch = enemy.getSymbol();
                            color_pair = enemy.getColor();
                            break;
                        }
                    }

                    // Check for items
                    for (const auto& item : items) {
                        if (item.getXCoordinate() == map_x && item.getYCoordinate() == map_y) {
                            ch = item.getSymbol();
                            color_pair = item.getColor();
                            break;
                        }
                    }
                } else if (!map.getTile(map_x, map_y).getInFOV() && map.getTile(map_x, map_y).getVisited()) {
                    ch = map.getTile(map_x, map_y).getSymbol();
                    color_pair = 0;
                }
            }

            // Set color and render character
            wattron(win, COLOR_PAIR(color_pair));
            mvwaddch(win, y, x, ch);
            wattroff(win, COLOR_PAIR(color_pair));
        }
    }

    mvwaddch(win, VIEWPORT_HEIGHT / 2, VIEWPORT_WIDTH / 2, player.getSymbol());
}

// Draws the command log
void UI::drawLog(WINDOW *win, const std::vector<std::string> &commandLog, size_t logIndex) {
    werase(win);
    wattron(win, COLOR_PAIR(0));
    box(win, 0, 0);
    for (size_t i = 0; i < LOG_LINES; i++) {
        size_t index = (logIndex + i) % LOG_LINES;
        if (index < commandLog.size()) {
            mvwprintw(win, i + 1, 1, "%s", commandLog[index].c_str());
        }
    }
    wattroff(win, COLOR_PAIR(0));
    wrefresh(win);
}

// Draws the player's info panel
void UI::drawInfo(WINDOW *win, const Player &player) {
    werase(win);
    wattron(win, COLOR_PAIR(0));
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Info Panel");
    mvwprintw(win, 2, 1, "Name: %s", player.getName().c_str());
    mvwprintw(win, 3, 1, "Position: (%d, %d)", player.getXCoordinate(), player.getYCoordinate());
    mvwprintw(win, 4, 1, "Health: %d", player.getHealth());
    mvwprintw(win, 5, 1, "Attack: %d", player.getAttack());
    mvwprintw(win, 6, 1, "Inventory: %ld", player.getInventory().size());
    wattroff(win, COLOR_PAIR(0));
    wrefresh(win);
}

// Draws the inventory screen
void UI::drawInventory(WINDOW *win, const Player &player) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Inventory:");

    const auto& inventory = player.getInventory();
    size_t max_lines = 9;
    size_t start_line = 0;
    size_t selected_item = 0;
    int ch;

    keypad(win, TRUE); // Enable keypad for special keys

    // Main loop for displaying inventory
    while (true) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 1, 2, "Inventory:");

        // Display the items with highlighting
        for (size_t i = 0; i < max_lines && start_line + i < inventory.size(); ++i) {
            if (i + start_line == selected_item) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 2, 2, "%zu: %s", start_line + i + 1, inventory[start_line + i].getName().c_str());
            wattroff(win, A_REVERSE);
        }

        wrefresh(win); 

        // Handle user input for scrolling or closing
        ch = wgetch(win);
        if (ch == 'q') {
            break;
        } else if (ch == KEY_UP && selected_item > 0) {
            selected_item--; // Move selection up
            if (selected_item < start_line) {
                start_line--; // Scroll up if needed
            }
        } else if (ch == KEY_DOWN && selected_item < inventory.size() - 1) {
            selected_item++; // Move selection down
            if (selected_item >= start_line + max_lines) {
                start_line++; // Scroll down if needed
            }
        } else if (ch == KEY_ENTER || ch == '\n') {
            if (selected_item < inventory.size()) {
                // Create a new window to display the item details
                WINDOW *detail_win = newwin(12, 50, (LINES - 12) / 2, (COLS - 50) / 2);
                box(detail_win, 0, 0);
                
                // Get selected item
                const auto& item = inventory[selected_item];
                mvwprintw(detail_win, 1, 2, "Name: %s", item.getName().c_str()); // Adjusted position
                
                // Wrap the description text
                mvwprintw(detail_win, 3, 2, "Description:"); // Header for description
                wrapPrint(detail_win, item.getDescription(), 4, 2, 36); // Wrap description text
                wrefresh(detail_win);
                
                // Wait for user input to close the detail window
                while (true) {
                    int detail_ch = wgetch(detail_win);
                    if (detail_ch == 'q') {
                        werase(detail_win);
                        wrefresh(detail_win);
                        break;
                    }
                }
                delwin(detail_win);
            }
        }
    }

    werase(win);
    wrefresh(win); 
}
