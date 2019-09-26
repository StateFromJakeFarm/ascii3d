/**
 * @file player.cpp
 * @author Jake Hansen
 *
 * Implementation of Player class.
 */

#include "player.h"

/**
 * Player object constructor.
 *
 * @param game_map_ptr Pointer to GameMap object containing player environment
 * @param y Starting y position in map file
 * @param x Starting x position in map file
 * @param view_angle Starting view direction in radians
 * @param fov Player's angle of view in radians
 * @param walk_speed Speed multiplier for x and y directions of player
 *        movement
 * @param turn_speed Turning multiplier for player's turning speed
 *
 * @return Player object
 */
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

/**
 * Turn player to the right one increment.
 *
 * @return void
 */
void Player::turn_right() {
    view_angle += turn_speed;
}

/**
 * Turn player to the left one increment.
 *
 * @return void
 */
void Player::turn_left() {
    view_angle -= turn_speed;
}

/**
 * Move player forward one increment relative to current
 * view_angle.
 *
 * @return void
 */
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

/**
 * Move player backward one increment relative to current
 * view_angle.
 *
 * @return void
 */
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

/**
 * Move player to the right one increment relative to current
 * view_angle.
 *
 * @return void
 */
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

/**
 * Move player to the left one increment relative to current
 * view_angle.
 *
 * @return void
 */
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
