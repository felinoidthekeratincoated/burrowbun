#include "Game.hh"
#include <iostream>
#include <string>
#include <libgen.h> // For dirname
#include <unistd.h> // For readlink

using namespace std;

int main(int argc, char **argv) {
    /* The path to the executable, linux-only. */
    int PATH_MAX = 512;
    char result[ PATH_MAX ];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX - 1);
    std::string path;
    if (count != -1) {
        result[count] = '\0';
        path = dirname(result);
    }
    else {
        cerr << "Unable to get path to executable!\nExiting...\n";
        exit(1);
    }
    path = path + "/";

    Game game(path);
    game.run();
    // Clean up fonts
    Texture::closeFonts();
    return 0;
}


