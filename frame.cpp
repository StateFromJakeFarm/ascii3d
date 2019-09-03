#include "frame.h"

Frame::Frame(GameMap *game_map_ptr, Player *player_ptr, int rows, int cols,
    int render_dist, double corner_resolution) {

    picture.resize(rows);
    for (auto &row : picture) {
        row = new wchar_t[cols + 1]; // Extra space for null-terminator
        row[cols] = '\0';
    }

    this->game_map_ptr = game_map_ptr;
    this->player_ptr = player_ptr;
    this->screen_rows = rows;
    this->screen_cols = cols;
    this->render_dist = render_dist;
    this->corner_resolution = corner_resolution;
}

Frame::~Frame() {
    for (auto &row : picture) {
        delete []row;
    }
}

bool Frame::is_corner(const double y_test, const double x_test) {
    return (fabs(round(y_test) - y_test) <= corner_resolution &&
        fabs(round(x_test) - x_test) <= corner_resolution);
}

void Frame::render() {
    double ray_angle, dist, y_test, x_test, ceiling, floor, floor_dist_factor;

    for (int col=0; col<screen_cols; col++) {
        // Begin casting rays at left of view, casting one ray for each
        // column in the screen
        ray_angle = (player_ptr->get_view() - player_ptr->get_fov()/2.0) +
            ((double)col / (double)screen_cols) * player_ptr->get_fov();

        // Calculate distance from player to wall (or edge of map) for this ray
        dist = 0.0;
        do {
            dist += 0.1;

            y_test = player_ptr->get_y() + cos(ray_angle) * dist;
            x_test = player_ptr->get_x() + sin(ray_angle) * dist;
        } while (dist <= render_dist && game_map_ptr->at(y_test, x_test) != '#');

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
                    if (is_corner(y_test, x_test)) {
                        val = '|';
                    } else {
                        val = 0x2588;
                    }
                } else if (dist <= render_dist / 3) {
                    if (is_corner(y_test, x_test)) {
                        val = ' ';
                    } else {
                        val = 0x2593;
                    }
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
