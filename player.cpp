#include "player.h"

Player::Player(GameMap *game_map_ptr, double y, double x, double view_angle,
    double fov, double walk_speed, double turn_speed) {
    this->game_map_ptr = game_map_ptr;
    this->y = y;
    this->x = x;
    this->view_angle = view_angle;
    this->fov = fov;
    this->walk_speed = walk_speed;
    this->turn_speed = turn_speed;
}

void Player::turn_right() {
    view_angle += turn_speed;
}

void Player::turn_left() {
    view_angle -= turn_speed;
}

void Player::walk_forward() {
    double step_x = walk_speed * sin(view_angle);
    double step_y = walk_speed * cos(view_angle);

    if (game_map_ptr->at(y + step_y, x + step_x) != '#') {
        x += step_x;
        y += step_y;
    } else if (game_map_ptr->at(y + step_y, x) != '#') {
        y += step_y;
    } else if (game_map_ptr->at(y, x + step_x) != '#') {
        x += step_x;
    }
}

void Player::walk_backward() {
    double step_x = walk_speed * sin(view_angle);
    double step_y = walk_speed * cos(view_angle);

    if (game_map_ptr->at(y - step_y, x - step_x) != '#') {
        x -= step_x;
        y -= step_y;
    } else if (game_map_ptr->at(y - step_y, x) != '#') {
        y -= step_y;
    } else if (game_map_ptr->at(y, x - step_x) != '#') {
        x -= step_x;
    }

}

void Player::strafe_right() {
    double step_x = walk_speed * cos(view_angle);
    double step_y = walk_speed * sin(view_angle);

    if (game_map_ptr->at(y - step_y, x + step_x) != '#') {
        x += step_x;
        y -= step_y;
    } else if (game_map_ptr->at(y - step_y, x) != '#') {
        y -= step_y;
    } else if (game_map_ptr->at(y, x + step_x) != '#') {
        x += step_x;
    }
}

void Player::strafe_left() {
    double step_x = walk_speed * cos(view_angle);
    double step_y = walk_speed * sin(view_angle);

    if (game_map_ptr->at(y + step_y, x - step_x) != '#') {
        x -= step_x;
        y += step_y;
    } else if (game_map_ptr->at(y + step_y, x) != '#') {
        y += step_y;
    } else if (game_map_ptr->at(y, x - step_x) != '#') {
        x -= step_x;
    }
}
