#include <iostream>
#include "Hotbar.hh"
#include "filepaths.hh"

// The number of slots in the hotbar

using namespace std;

// Constructor, which fills it with default values
Hotbar::Hotbar(string path) {
    // If you want to change these default settings, this is the place in the 
    // code to do it.
    smallGap = 4;
    largeGap = 16;
    offsetRight = 8;
    offsetDown = 8;
    // Where to draw the hotbar
    xStart = 20;
    yStart = 10;

    /* TODO: move magic numbers to a json file or something. */
    /* x, y, w, h, name */
    frame = Sprite(0, 0, 32, 32, "frame.png");

    int spriteWidth = 12 * frame.getWidth() + 12 * smallGap + 2 * largeGap 
        + offsetRight;
    int spriteHeight = frame.getHeight() + offsetDown;
    sprite = Sprite(0, 0, spriteWidth, spriteHeight, "");

    isSpriteUpdated = false;

    isSwitched = false;
    selected = 0;

    clickBoxes.resize(12);

    int x = xStart + offsetRight;
    // For each section of four
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int index = 4 * i + j;
            clickBoxes[index].x = x;
            clickBoxes[index].y = yStart + offsetDown;
            clickBoxes[index].w = frame.getWidth();
            clickBoxes[index].h = frame.getHeight();
            clickBoxes[index].wasClicked = false;
            clickBoxes[index].containsMouse = false;
            x += frame.getWidth() + smallGap;
        }
        x += largeGap;
    }

    // Set every action * to NULL
    actions.resize(24);
    for (unsigned int i = 0; i < actions.size(); i++) {
        actions[i] = NULL;
    }

    /* Load the frame's texture. */
    frame.loadTexture(path + UI_SPRITE_PATH);
}

// Toggle which row is on top
void Hotbar::toggle() {
    isSwitched = !isSwitched;
    isSpriteUpdated = false;
}

// Select a slot
void Hotbar::select(int slot) {
    if (slot != selected) {
        selected = slot;
        isSpriteUpdated = false;
    }
}

// Use mouse input, return true if the item the mouse was holding should
// be put in the inventory
bool Hotbar::update(Action *mouse) {
    bool answer = false;
    for (unsigned int i = 0; i < clickBoxes.size(); i++) {
        // Ignore mouse button up or mouse button held down
        if (clickBoxes[i].wasClicked && !clickBoxes[i].isHeld
                && clickBoxes[i].event.type == SDL_MOUSEBUTTONDOWN ) {
            // Add 12 to i if isSwitched
            int adjusted = i + 12 * (int)isSwitched;
            /* Select it if it wasn't already. */
            select(adjusted);
            // See if we should put something in the slot
            if (clickBoxes[i].event.button == SDL_BUTTON_LEFT
                    && mouse != NULL) {
                actions[adjusted] = mouse;
                // If it's an item, put it back in the inventory
                if (mouse -> isItem) {
                    answer = true;
                }
                /* And now the sprite needs to change. */
                isSpriteUpdated = false;
            }
            // If it was a right click, we should remove that item from the
            // hotbar.
            else if (clickBoxes[i].event.button == SDL_BUTTON_RIGHT) {
                actions[adjusted] = NULL;
                /* And again the sprite needs to change. */
                isSpriteUpdated = false;
            }
            /* Now we've used this click. */
            clickBoxes[i].wasClicked = false;
        }
    }
    return answer;
}

// Return the selected action
Action *Hotbar::getSelected() {
    return actions[selected];
}
