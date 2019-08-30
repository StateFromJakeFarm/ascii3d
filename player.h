#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "game_map.h"

class Player {
    private:
    // Position & orientation
    double x, y, view_angle;

    // Movement stats
    double fov, walk_speed, turn_speed;

    public:
    // Player movement
    Player(double, double, double);
    void turn_right(double);
    void turn_left(double);
    void walk_forward(GameMap&, double);
    void walk_backward(GameMap&, double);
    void strafe_right(GameMap&, double);
    void strafe_left(GameMap&, double);
};

#endif
