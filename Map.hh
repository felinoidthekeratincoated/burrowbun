#ifndef MAP_HH
#define MAP_HH

#include <vector>
#include <string>
#include <random> // For the fancy randomness like a normal distribution
#include "Tile.hh"
#include "MapHelpers.hh"

using namespace std;

// A class for a map for a sandbox game
// Currently its only focus is on generating the map
class Map {
    // Fields:

    // The array to hold the map info
    // This is a 2d array squished into 1d
    SpaceInfo *tiles;

    // A list of the pointers in the map
    // Basically these are the ones that contain manually allocated memeory
    vector<Tile *> pointers;

    // The height and width of the map, in number of tiles
    int height, width;

    // Default spawn point
    Location spawn;

    // Have a random number generator
    default_random_engine generator;

    // Private methods

    // Really small helper functions that don't directly change tiles

    // Return a pointer to the SpaceInfo* at x, y
    SpaceInfo *findPointer(int x, int y) const;

    /* Make a Tile object, add it to the list of pointers, and return 
       a pointer to it. */
    Tile *newTile(TileType val);

    // Find a Tile object of type val. If it does not exist, create it. If
    // multiple exist, return the first one.
    Tile *makeTile(TileType val);

    // Set all tiles to val
    //void setAll(Tile* const &val);

    // Start at top and go down until the type changes
    // Return the height of the first tile of a different type
    // Return -1 if there is no change
    //int findChange(int x, int top) const;
    public:

    // Contructs a map by loading a file
    Map(string filename);

    // Destructor
    ~Map();

    // Return the height of the map, in number of tiles
    int getHeight() const;

    // Return the width of the map, in number of tiles
    int getWidth() const;

    // Return the default spawn point
    Location getSpawn() const;

    // Return which part of the spritesheet should be used
    Location getSpritePlace(int x, int y) const;

    // Returns the foreground tile pointer at x, y
    // 0, 0 is the bottom right
    Tile *getForeground(int x, int y) const;

    // Returns the background tile pointer at x, y
    // 0, 0 is the bottom right
    Tile *getBackground(int x, int y) const;

    // Set the foreground tile at x, y equal to val
    void setForeground(int x, int y, Tile* const &val);

    // Set the background tile at x, y equal to val
    void setBackground(int x, int y, Tile* const &val);

    // Gets the map's list of the tile pointers it uses
    vector<Tile *> getPointers() const;

    // Gets a reference to the map's list of the tile pointers it uses
    // This might only be for setting the tile textures
    vector<Tile *> &getPointersRef();

    // Write the map to a file
    void save(const string &filename) const;
};

#endif
