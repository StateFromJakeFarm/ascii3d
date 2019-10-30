/**
 * @file game_map.cpp
 * @author Jake Hansen
 *
 * Implementation of GameMap class.
 */

#include "game_map.h"

/**
 * Constructor for GameMap class.
 *
 * @param file Path to map file
 *
 * @return GameMap object
 */
GameMap::GameMap(string file) {
    // Open file
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
        // Map file improperly formatted
        cerr << "Error: map must be rectangular" << endl;
        exit(1);
    }
}

/**
 * Return the character at a certain position in the map.
 *
 * @param row Index of row in map file
 * @param col Index of column in map file
 *
 * @return char at requested position
 */
char GameMap::at(const int row, const int col) {
    if (row < 0 || col < 0 || row >= height || col >= width) {
        return ' ';
    }

    return map[row][col];
}
