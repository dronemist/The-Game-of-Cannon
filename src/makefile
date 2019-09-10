# Compiler to use
CXX = g++ -std=c++11

# Flags
CXXFLAGS = -Wall -g

# Executable name
OUT = main

all: $(OUT)

# Executable
$(OUT): board.o position.o soldier.o townhall.o cannon.o
	$(CXX) board.o position.o soldier.o townhall.o cannon.o -o main $(CXXFLAGS)

# Main
# main.o: board.cpp soldier.h townhall.h cannon.h

# Board
board.o: board.cpp board.h cannon.h soldier.h townhall.h 
	$(CXX) -c board.cpp -o $@

# Cannon
cannon.o: piece.h position.h board.h cannon.h
	$(CXX) -c cannon.cpp -o $@

# # State
# state.o: state.h fileReader.h

# Soldier
soldier.o: piece.h position.h board.h soldier.h
	$(CXX) -c soldier.cpp -o $@

# Expand
townhall.o: piece.h position.h board.h soldier.h
	$(CXX) -c townhall.cpp -o $@

# Position
position.o: position.h

# Clean
clean:
	rm *.o
	rm $(OUT)