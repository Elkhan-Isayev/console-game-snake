# Simple cross-platform build for the console Snake game.
CXX      ?= c++
CXXFLAGS ?= -std=c++17 -Wall -O2
SRC      := game-snake/game-snake.cpp
BIN      := game-snake/game-snake

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
