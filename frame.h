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

    public:
    int screen_rows, screen_cols, render_dist;
    vector<wchar_t*> picture;
    Frame(GameMap*, Player*, int, int, int);
    ~Frame();

    void render();
};

#endif
