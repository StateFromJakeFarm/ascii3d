#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "game_map.h"

class Player {
    private:
    GameMap *game_map_ptr;
    double x, y, view_angle;
    double fov, walk_speed, turn_speed;

    public:
    // Player movement
    Player(GameMap*, double, double, double, double, double, double);
    void turn_right();
    void turn_left();
    void walk_forward();
    void walk_backward();
    void strafe_right();
    void strafe_left();

    // Getters
    double get_x() {return x;}
    double get_y() {return y;}
    double get_view() {return view_angle;}
    double get_fov() {return fov;}
};

#endif
