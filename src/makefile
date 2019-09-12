# Compiler to use
CXX = g++ -std=c++11

# Flags
CXXFLAGS = -Wall -g

# Executable name
OUT = main

all: $(OUT)

# Executable
$(OUT): main.o board.o position.o soldier.o townhall.o state.o search.o gamePlayer.o
	$(CXX) board.o position.o soldier.o townhall.o state.o search.o gamePlayer.o main.o -o $(OUT) $(CXXFLAGS)

# Main
main.o: gamePlayer.h state.h board.h piece.h position.h soldier.h townhall.h
	$(CXX) -c main.cpp -o $@
# Board
board.o: board.h soldier.h townhall.h
	$(CXX) -c board.cpp -o $@

# GamePlayer
gamePlayer.o: search.h state.h gamePlayer.h
	$(CXX) -c gamePlayer.cpp -o $@

# Cannon
# cannon.o: piece.h position.h board.h cannon.h
# 	$(CXX) -c cannon.cpp -o $@

# State
state.o: state.h board.h
	$(CXX) -c state.cpp -o $@
# Search
search.o: search.h state.h
	$(CXX) -c search.cpp -o $@
# Soldier
soldier.o: piece.h position.h board.h soldier.h
	$(CXX) -c soldier.cpp -o $@

# Townhall
townhall.o: piece.h position.h board.h townhall.h
	$(CXX) -c townhall.cpp -o $@

# Position
position.o: position.h
	$(CXX) -c position.cpp -o $@
# Clean
clean:
	rm *.o
	rm $(OUT)