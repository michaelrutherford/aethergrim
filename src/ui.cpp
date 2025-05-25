// MIT License
// Copyright (c) 2024- Michael Rutherford

#include "ui.h"

// Default constructor
UI::UI() { initialize(); }

// Destructor to clean up
UI::~UI() { endwin(); }

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
  init_pair(1, COLOR_BLUE, COLOR_BLACK);    // Wall color
  init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Ground color
  init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Visited tiles color
  init_pair(4, COLOR_BLACK, COLOR_BLACK);   // Unvisited tiles color
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // Info color
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);  // Item color
  init_pair(7, COLOR_RED, COLOR_BLACK);     // Enemy color
}

// Prints text word-wrapped in the given window
void UI::wrapPrint(WINDOW *win, const std::string &text, int start_y,
                   int start_x, int width) {
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
  wrefresh(win);
  // Enable arrow keys for menu
  keypad(win, TRUE);

  const std::vector<std::string> options = {"New Game", "Help", "Credits",
                                            "Quit"};
  size_t selected_item = 0;
  int ch = ' ';

  // Main loop for displaying the menu
  while (true) {
    werase(win);

    // Print ASCII art title
    wattron(win, COLOR_PAIR(2));
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
    mvwprintw(win, 8, COLS / 2 - 30, "                                  __/ |");
    mvwprintw(win, 9, COLS / 2 - 30,
              "                                 |___/   ");
    wattroff(win, COLOR_PAIR(2));

    // Highlight selected menu option
    for (size_t i = 0; i < options.size(); ++i) {
      if (i == selected_item) {
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, (LINES / 2) + i - (options.size() / 2), COLS / 2 - 7, "%s",
                options[i].c_str());
      wattroff(win, A_REVERSE);
    }

    wrefresh(win); // Refresh to show options

    // Handle user input
    ch = wgetch(win);
    if (ch == KEY_UP && selected_item > 0) {
      selected_item--; // Move selection up
    } else if (ch == KEY_DOWN && selected_item < options.size() - 1) {
      selected_item++; // Move selection down
    } else if (ch == KEY_ENTER || ch == '\n') {
      switch (selected_item) {
      case 0:
        return; // New Game
      case 1:
        drawHelp();
        selected_item = 0;
        break;
      case 2:
        drawCredits();
        selected_item = 0;
        break;
      case 3:
        endwin();
        exit(0);
      }
    }
  }
}

// Draws the credits menu
void UI::drawCredits() {
  WINDOW *credits_win = newwin(LINES, COLS, 0, 0);
  int ch = ' ';
  werase(credits_win);
  box(credits_win, 0, 0);
  mvwprintw(credits_win, 1, COLS / 2 - 6, "Credits");
  mvwprintw(credits_win, 3, 2, "Created by: Michael Rutherford");
  mvwprintw(credits_win, 4, 2, "Aethergrim is released under the MIT License.");
  mvwprintw(credits_win, 5, 2, "For more information, see `LICENSE`.");
  while (true) {
    ch = wgetch(credits_win);
    if (ch == 'q') {
      break;
    }
  }
  werase(credits_win);
  wrefresh(credits_win);
  delwin(credits_win);
}

// Draws the help screen
void UI::drawHelp() {
  WINDOW *credits_win = newwin(LINES, COLS, 0, 0);
  int ch = ' ';
  werase(credits_win);
  box(credits_win, 0, 0);
  mvwprintw(credits_win, 1, COLS / 2 - 6, "Help");
  mvwprintw(credits_win, 3, 2, "[UP ARROW]: Move up");
  mvwprintw(credits_win, 4, 2, "[DOWN ARROW]: Move down");
  mvwprintw(credits_win, 5, 2, "[LEFT ARROW]: Move left");
  mvwprintw(credits_win, 6, 2, "[RIGHT ARROW]: Move right");
  mvwprintw(credits_win, 7, 2, "[i]: Open inventory");
  mvwprintw(credits_win, 8, 2, "[q]: Back/quit");

  while (true) {
    ch = wgetch(credits_win);
    if (ch == 'q') {
      break;
    }
  }
  werase(credits_win);
  wrefresh(credits_win);
  delwin(credits_win);
}

// Draws the game viewport centered around the player
void UI::drawViewport(WINDOW *win, const Player &player,
                      const std::vector<Enemy> &enemies,
                      const std::vector<Item> &items, const Map &map) {
  int playerX = player.getXCoordinate();
  int playerY = player.getYCoordinate();

  for (int y = 0; y < VIEWPORT_HEIGHT; y++) {
    for (int x = 0; x < VIEWPORT_WIDTH; x++) {
      int map_x = playerX - VIEWPORT_WIDTH / 2 + x;
      int map_y = playerY - VIEWPORT_HEIGHT / 2 + y;

      char ch = ' ';
      int color_pair = 4;

      // Check if within map boundaries
      if (map_y >= 0 && map_y < map.MAP_HEIGHT && map_x >= 0 &&
          map_x < map.MAP_WIDTH) {
        // Check if the tile is in FOV
        if (map.getTile(map_x, map_y).getInFOV()) {
          ch = map.getTile(map_x, map_y).getSymbol();
          color_pair = map.getTile(map_x, map_y).getColor();

          // Check for enemies
          for (const auto &enemy : enemies) {
            if (enemy.getXCoordinate() == map_x &&
                enemy.getYCoordinate() == map_y) {
              ch = enemy.getSymbol();
              color_pair = enemy.getColor();
              break;
            }
          }

          // Check for items
          for (const auto &item : items) {
            if (item.getXCoordinate() == map_x &&
                item.getYCoordinate() == map_y) {
              ch = item.getSymbol();
              color_pair = item.getColor();
              break;
            }
          }
        } else if (!map.getTile(map_x, map_y).getInFOV() &&
                   map.getTile(map_x, map_y).getVisited()) {
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
void UI::drawLog(WINDOW *win, Log &log, size_t logIndex) {
  werase(win);
  wattron(win, COLOR_PAIR(0));
  for (size_t i = 0; i < Log::LOG_LINES; i++) {
    size_t index = (logIndex + i) % Log::LOG_LINES;
    if (index < log.command_log.size()) {
      mvwprintw(win, i + 1, 1, "- %s", log.command_log[index].c_str());
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
  mvwprintw(win, 3, 1, "Health: %d", player.getHealth());
  mvwprintw(win, 4, 1, "Attack: %d", player.getAttack());
  mvwprintw(win, 5, 1, "Inventory: %ld", player.getInventory().size());
  mvwprintw(win, 6, 1, "Depth: %d", Map::getInstance().getDepth());
  mvwprintw(win, 7, 1, "Position: (%d, %d)", player.getXCoordinate(),
            player.getYCoordinate());
  wattroff(win, COLOR_PAIR(0));
  wrefresh(win);
}

// Draws the inventory screen
void UI::drawInventory(WINDOW *win, Player &player) {
  werase(win);
  box(win, 0, 0);
  mvwprintw(win, 1, 2, "Inventory:");

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

    auto inventory = player.getInventory();
    // Display the items with highlighting
    for (size_t i = 0; i < max_lines && start_line + i < inventory.size();
         ++i) {
      if (i + start_line == selected_item) {
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, i + 2, 2, "%zu: %s", start_line + i + 1,
                inventory[start_line + i].getName().c_str());
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
        drawItemDetails(player, selected_item);
        selected_item = 0;
        start_line = 0;
      }
    }
  }
  werase(win);
  wrefresh(win);
}

// Draws the details of the selected item
void UI::drawItemDetails(Player &player, size_t index) {
  const int win_height = 12;
  const int win_width = 50;

  // Create a new window to display the item details
  WINDOW *detail_win = newwin(win_height, win_width, (LINES - win_height) / 2,
                              (COLS - win_width) / 2);
  WINDOW *option_win =
      newwin(5, win_width, (LINES + win_height) / 2, (COLS - win_width) / 2);

  // Enable arrow keys for menu
  keypad(option_win, TRUE);
  const std::vector<std::string> options = {"Back", "Use", "Drop"};
  size_t selected_item = 0;
  int ch;

  // Get selected item
  const auto &item = player.getItemAt(index);

  // Main loop for displaying the menu
  while (true) {
    werase(detail_win);

    // Draw borders and title
    box(detail_win, 0, 0);
    box(option_win, 0, 0);
    mvwprintw(detail_win, 1, 2, "Name: %s",
              item.getName().c_str()); // Adjusted position

    // Wrap the description text
    mvwprintw(detail_win, 3, 2, "Description:"); // Header for description
    wrapPrint(detail_win, item.getDescription(), 4, 2,
              36); // Wrap description text

    // Highlight selected menu option
    for (size_t i = 0; i < options.size(); ++i) {
      if (i == selected_item) {
        wattron(option_win, A_REVERSE);
      }
      mvwprintw(option_win, 1 + i, 1, "%s", options[i].c_str());
      wattroff(option_win, A_REVERSE);
    }

    wrefresh(detail_win); // Refresh to show options
    wrefresh(option_win);

    // Handle user input
    ch = wgetch(option_win);
    if (ch == KEY_UP && selected_item > 0) {
      selected_item--; // Move selection up
    } else if (ch == KEY_DOWN && selected_item < options.size() - 1) {
      selected_item++; // Move selection down
    } else if (ch == KEY_ENTER || ch == '\n') {
      switch (selected_item) {
      case 0:
        werase(option_win);
        wrefresh(option_win);
        return;
      case 1:
        player.useItem(index);
        werase(option_win);
        wrefresh(option_win);
        return;
      case 2:
        player.removeFromInventory(index);
        werase(detail_win);
        werase(option_win);
        wrefresh(detail_win);
        wrefresh(option_win);
        return;
      }
    }
  }
  delwin(detail_win);
  delwin(option_win);
}

// Displays the game over menu and handles user input
void UI::drawGameOver(WINDOW *win) {
  werase(win);

  // Enable arrow keys for menu
  keypad(win, TRUE);

  const std::vector<std::string> options = {"Main Menu", "Quit"};
  size_t selected_item = 0;
  int ch;

  // Main loop for displaying the menu
  while (true) {
    werase(win);

    if (Map::getInstance().getDepth() <= 3) {
      wattron(win, COLOR_PAIR(7));
      mvwprintw(win, 1, COLS / 2 - 7, "GAME OVER");
      wattroff(win, COLOR_PAIR(7));
    } else {
      wattron(win, COLOR_PAIR(2));
      mvwprintw(win, 1, COLS / 2 - 7, "GAME OVER");
      wattroff(win, COLOR_PAIR(2));
      mvwprintw(win, 3, 3, "You have found the Ring.");
    }

    // Highlight selected menu option
    for (size_t i = 0; i < options.size(); ++i) {
      if (i == selected_item) {
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, (LINES / 2) + i - (options.size() / 2), COLS / 2 - 7, "%s",
                options[i].c_str());
      wattroff(win, A_REVERSE);
    }

    wrefresh(win); // Refresh to show options

    // Handle user input
    ch = wgetch(win);
    if (ch == KEY_UP && selected_item > 0) {
      selected_item--; // Move selection up
    } else if (ch == KEY_DOWN && selected_item < options.size() - 1) {
      selected_item++;                          // Move selection down
    } else if (ch == KEY_ENTER || ch == '\n') { // Enter key
      switch (selected_item) {
      case 0:
        return;
      case 1:
        endwin();
        exit(0);
      }
    }
  }
}

// Displays the quit confirmation menu
void UI::drawQuit() {
  WINDOW *quit_win = newwin(LINES, COLS, 0, 0);

  // Enable arrow keys for menu
  keypad(quit_win, TRUE);

  const std::vector<std::string> options = {"Continue", "Quit"};
  size_t selected_item = 0;
  int ch;

  // Main loop for displaying the quit confirmation
  while (true) {
    werase(quit_win);

    mvwprintw(quit_win, 1, COLS / 2 - 7, "QUIT");
    mvwprintw(quit_win, 3, 3, "Are you sure you want to quit?");

    // Highlight selected menu option
    for (size_t i = 0; i < options.size(); ++i) {
      if (i == selected_item) {
        wattron(quit_win, A_REVERSE);
      }
      mvwprintw(quit_win, (LINES / 2) + i - (options.size() / 2), COLS / 2 - 7,
                "%s", options[i].c_str());
      wattroff(quit_win, A_REVERSE);
    }

    wrefresh(quit_win); // Refresh to show options

    // Handle user input
    ch = wgetch(quit_win);
    if (ch == KEY_UP && selected_item > 0) {
      selected_item--; // Move selection up
    } else if (ch == KEY_DOWN && selected_item < options.size() - 1) {
      selected_item++;                          // Move selection down
    } else if (ch == KEY_ENTER || ch == '\n') { // Enter key
      switch (selected_item) {
      case 0:
        werase(quit_win);
        return; // Return to the game
      case 1:
        endwin(); // End NCurses mode
        exit(0);  // Exit the game
      }
    }
  }
}
