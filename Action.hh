#ifndef ACTION_HH
#define ACTION_HH

#include "Sprite.hh"

// Forward declare
class Player;
class Map;

// A class to describe how the player is trying to use an item
enum class InputType {
    NONE,
    LEFT_BUTTON_PRESSED,
    RIGHT_BUTTON_PRESSED,
    LEFT_BUTTON_HELD,
    RIGHT_BUTTON_HELD
};

/* A class for storing things that can go on the hotbar (items, skills). */
class Action {
protected:
    // Minimum time before another action can be done
    int useTime;

public:
    // Virtual destructor
    inline virtual ~Action() {};

    // What sprite should be displayed in the hotbar
    Sprite sprite;

    // Whether it's an item
    bool isItem;

    // Constructor
    inline Action() {
        /* TODO: get magic numbers from somewhere else. These are inventory
        square width and height. */
        sprite.width = 32;
        sprite.height = 32;
        useTime = 1;
    };

    /* Do the action, or use the item or skill. */
    inline virtual void 
            use(InputType type, int x, int y, Player &player, Map &map) {}

    // Access function
    inline int getUseTime() const {
        return useTime;
    }
};


#endif
