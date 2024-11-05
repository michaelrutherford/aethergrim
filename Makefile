# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall

# Libraries
LIBS = -lncurses

# Source files
SRCS = src/main.cpp src/player.cpp src/enemy.cpp src/map.cpp src/tile.cpp src/game.cpp src/item.cpp src/ui.cpp

# Output executable
TARGET = grumacetus

# Build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Clean up the build
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
