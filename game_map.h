#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using std::string;
using std::ifstream;
using std::getline;
using std::vector;
using std::cerr;
using std::endl;

class GameMap {
    private:
    vector<string> map;
    int height;
    int width;

    public:
    GameMap(string);

    // Getters
    int get_height() {return height;}
    int get_width() {return width;}
    char at(const int, const int);
};

#endif
