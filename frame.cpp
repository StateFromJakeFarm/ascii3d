#include "frame.h"

Frame::Frame(GameMap *game_map_ptr, Player *player_ptr, int rows, int cols,
    int render_dist) {

    picture.resize(rows);
    for (int i=0; i<rows; i++) {
        picture[i].resize(cols);
    }

    this->game_map_ptr = game_map_ptr;
    this->player_ptr = player_ptr;
    this->render_dist = render_dist;
    this->screen_rows = rows;
    this->screen_cols = cols;
}

void Frame::render() {
    double ray_angle, dist, test_y, test_x, ceiling, floor, floor_dist_factor;

    for (int col=0; col<screen_cols; col++) {
        // Begin casting rays at left of view, casting one ray for each
        // column in the screen
        ray_angle = (player_ptr->get_view() - player_ptr->get_fov()/2.0) +
            ((double)col / (double)screen_cols) * player_ptr->get_fov();

        // Calculate distance from player to wall (or edge of map) for this
        // ray
        dist = 0.0;
        do {
            dist += 0.1;

            test_y = player_ptr->get_y() + cos(ray_angle) * dist;
            test_x = player_ptr->get_x() + sin(ray_angle) * dist;
        } while (dist <= render_dist && game_map_ptr->at(test_y, test_x) != '#');

        // Determine floor and ceiling bounds
        ceiling = screen_rows / 2.0 - screen_rows / dist;
        floor = screen_rows - ceiling;

        // Fill this column with proper characters
        short val;
        for (int row=0; row<screen_rows; row++) {
            if (row < ceiling) {
                // Ceiling
                val = ' ';
            } else if (row >= ceiling && row < floor) {
                // Wall
                if (dist <= render_dist / 4) {
                    val = 0x2588;
                } else if (dist <= render_dist / 3) {
                    val = 0x2593;
                } else if (dist <= render_dist / 2) {
                    val = 0x2592;
                } else if (dist <= render_dist) {
                    val = 0x2591;
                } else {
                    val = ' ';
                }
            } else {
                // Floor
                floor_dist_factor = (double)(row - (screen_rows / 2)) / (double)(screen_rows / 2);
                if (floor_dist_factor >= 0.75) {
                    val = '#';
                } else if (floor_dist_factor >= 0.4) {
                    val = 'x';
                } else if (floor_dist_factor >= 0.25) {
                    val = '-';
                } else if (floor_dist_factor >= 0.1) {
                    val = '.';
                } else {
                    val = ' ';
                }
            }

            picture[row][col] = val;
        }
    }
}
