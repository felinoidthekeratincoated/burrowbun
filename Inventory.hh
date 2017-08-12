#ifndef INVENTORY_HH
#define INVENTORY_HH

#include <vector>
#include "Sprite.hh"
#include "UIHelpers.hh"
#include "Light.hh"
#include "Item.hh"

/* An inventory is basically just a thing that holds items. */
class Inventory {
    // For storing the list of items
    std::vector<std::vector<Item*>> items;

public:
    // Where the top left corner of the inventory is
    int x;
    int y;

    // For storing information about where has been clicked
    std::vector<std::vector<MouseBox>> clickBoxes;

    /* The sprite of the square to use for the background, which other than
    the color is the same for all inventories. */
    static Sprite squareSprite;

    /* Color with which to modulate the background squares. */
    Light squareColor;

    // The sprite of all the things, put together
    Sprite sprite;
    // Whether the sprite is updated
    bool isSpriteUpdated;

    // Constructor, given the size
    Inventory(int cols, int rows);

    /* Copy constructor. Don't use; all it does it assert false. If I ever
    think of any good reason why anyone would use a copy constructor of an
    inventory, I'll write a proper one. */
    Inventory(const Inventory &toCopy);

    /* operator=. Also don't use, also just asserts false. */
    Inventory &operator=(const Inventory &toCopy);

    // Destructor
    ~Inventory();

    // Access functions
    int getWidth() const;
    int getHeight() const;
    Item *getItem(int row, int col) const;
    void setItem(Item *item, int row, int col);

    // Put the item in the slot, if possible. If not possible, return false.
    Item *add(Item *item, int row, int col);

    // Take an item and put it in the first empty slot of the inventory. Return
    // false if there isn't room for it.
    Item *pickup(Item *item);

    // Call this after changing x or y, puts clickboxes in the right place
    void updateClickBoxes();

    // Use mouse input
    void update(Action *&mouse);
};

#endif
