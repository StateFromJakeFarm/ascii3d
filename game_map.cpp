#include "game_map.h"

GameMap::GameMap(string file) {
    ifstream file_obj(file);

    try {
        string row;
        width = 0;
        int i;
        for (i=0; getline(file_obj, row); i++) {
            if (width == 0) {
                // Grab map width after first row
                width = row.length();
            }

            if ((int)row.length() != width) {
                // Map must be rectangular
                throw 1;
            }

            map.push_back(row);
        }

        height = i;
    } catch (int e) {
        cerr << "Error: map must be rectangular" << endl;
        exit(1);
    }
}

char GameMap::at(const int row, const int col) {
    if (row < 0 || col < 0 || row >= height || col >= width) {
        return '.';
    }

    return map[row][col];
}
