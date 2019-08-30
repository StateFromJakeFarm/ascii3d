#include "player.h"

Player::Player(double y, double x, double view_angle,
    double fov, double walk_speed, double turn_speed) {
    this->y = y;
    this->x = x;
    this->view_angle = view_angle;
    this->fov = fov;
    this->walk_speed = walk_speed;
    this->turn_speed = turn_speed;
}

void Player::turn_right(double frame_duration) {
    view_angle += turn_speed * frame_duration;
}

void Player::turn_left(double frame_duration) {
    view_angle -= turn_speed * frame_duration;
}

void Player::walk_forward(GameMap &game_map, double frame_duration) {
    double step_x = walk_speed * sin(view_angle) * frame_duration;
    double step_y = walk_speed * cos(view_angle) * frame_duration;

    if (game_map.at(y + step_y, x + step_x) != '#') {
        x += step_x;
        y += step_y;
    }
}

void Player::walk_backward(GameMap &game_map, double frame_duration) {
    double step_x = walk_speed * sin(view_angle) * frame_duration;
    double step_y = walk_speed * cos(view_angle) * frame_duration;

    if (game_map.at(y - step_y, x - step_x) != '#') {
        x -= step_x;
        y -= step_y;
    }
}

void Player::strafe_right(GameMap &game_map, double frame_duration) {
    double step_x = walk_speed * cos(view_angle) * frame_duration;
    double step_y = walk_speed * sin(view_angle) * frame_duration;

    if (game_map.at(y - step_y, x + step_x) != '#') {
        x += step_x;
        y -= step_y;
    }
}

void Player::strafe_left(GameMap &game_map, double frame_duration) {
    double step_x = walk_speed * cos(view_angle) * frame_duration;
    double step_y = walk_speed * sin(view_angle) * frame_duration;

    if (game_map.at(y + step_y, x - step_x) != '#') {
        x -= step_x;
        y += step_y;
    }
}
