#include <string>
#include <cassert>

using namespace std;



// A class for keeping track of which tiles there are
enum class TileType {
    MAGMA,
    EMPTY,
    DIRT,
    STONE,
    PLATFORM,
    SANDSTONE,
    MUDSTONE
};

/* A class to make tiles based on their type, and store their infos. */
// Maybe since maps are filled with pointers to the same tile, everything
// should be constant
class Tile {
public:
    // The name of this type of tile
    const TileType type;

    // The height and width of the tile when displayed in game, in pixels
    const int height, width;

    // The name of the image file
    std::string sprite;

    // Variables for how it interacts with the players
    bool isPlatform; // Whether players collide with the underside
    // Player speed is multiplied by passage of the tiles the player is in
    double passage;

    // Variables to use in map generation and upkeep
    // In these ones, -1 means infinity
    float mass;        // How heavy one tile of it is
    float erodeResist;  // How hard it is to erode
    float maxPressure; // How much pressure before it metamorphoses
    // TODO: implement heat-based metamorphism
    TileType pressureMetamorph; // What it becomes

    // Constructor, based on the tile type
    // Also the only actual method Tiles have
    Tile(TileType tileType);
};
