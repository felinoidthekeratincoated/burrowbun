CC = g++
# For debugging use -Og -g
# For going fast use -O2 or -O3
CXXFLAGS = -std=c++14 -Wall -D_GLIBCXX_DEBUG -D_LIBCXX_DEBUG_PEDANTIC -Og -g
LINKER_FLAGS = -lSDL2 -lSDL2_image

all : main

main : main.o Map.o World.o Tile.o WindowHandler.o EventHandler.o Movable.o \
        Player.o Collider.o
	$(CC) $(CXXFLAGS) $(LINKER_FLAGS) $^ -o $@ $(LDFLAGS)

Map.o : Map.cc Map.hh Tile.hh MapHelpers.hh
	$(CC) $(CXXFLAGS) $^ -c $(LDFLAGS)

Tile.o : Tile.cc Tile.hh
	$(CC) $(CXXFLAGS) $^ -c $(LDFLAGS)

WindowHandler.o : WindowHandler.cc WindowHandler.hh Tile.hh Map.hh Movable.hh
	$(CC) $(CXXFLAGS) $(LINKER_FLAGS) $^ -c $(LDFLAGS)

EventHandler.o : EventHandler.cc EventHandler.hh WindowHandler.hh Player.hh
	$(CC) $(CXXFLAGS) $(LINKER_FLAGS) $^ -c $(LDFLAGS)

Movable.o : Movable.cc Movable.hh Point.hh
	$(CC) $(CXXFLAGS) $(LINKER_FLAGS) $^ -c $(LDFLAGS)

Player.o : Player.cc Player.hh Movable.hh
	$(CC) $(CXXFLAGS) $(LINKER_FLAGS) $^ -c $(LDFLAGS)

Collider.o : Collider.cc Collider.hh Tile.hh Map.hh Movable.hh
	$(CC) $(CXXFLAGS) $^ -c $(LDFLAGS)

World.o : World.cc World.hh Tile.hh MapHelpers.hh
	$(CC) $(CXXFLAGS) $^ -c $(LDFLAGS)

clean :
	rm -f *.o *.gch *~ *.world

.PHONY : all clean

