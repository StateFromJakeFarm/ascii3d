#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <string>
#include <utility>
#include "game_map.h"
#include "player.h"

using std::vector;
using std::pair;

class Frame {
    private:
    GameMap *game_map_ptr;
    Player *player_ptr;
    bool is_corner(const double, const double);

    public:
    int screen_rows, screen_cols, render_dist;
    double corner_resolution;
    vector<wchar_t*> picture;

    Frame(GameMap*, Player*, int, int, int, double);
    ~Frame();

    void render();
};

#endif
