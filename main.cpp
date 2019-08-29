#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>

using std::vector;
using std::wstring;
using std::chrono::system_clock;
using std::chrono::duration;

typedef vector< vector<short> > Frame;

struct Player {
    double y;
    double x;
    double angle;
};

bool hit_wall(const wstring &map, int map_y, int map_x, int y, int x,
    double dist, double render_dist) {

    return y < 0 || y >= map_y || x < 0 || x >= map_x ||
        map.c_str()[map_x*x + y] == '#' || dist >= render_dist;
}

char map_at(const wstring &map, int map_y, int map_x, int y, int x) {
    if (y < 0 || y >= map_y || x < 0 || x >= map_x) {
        return '#';
    }

    return map.c_str()[map_x*x + y];
}

void display_frame(const Frame &frame) {
    move(0, 0);
    for (auto line : frame) {
        wstring line_wstr;
        for (short c : line) {
            line_wstr += c;
        }
        addwstr(line_wstr.c_str());
    }

    wrefresh(stdscr);
}

int main() {
    // Configure Ncurses
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    // Store current "frame" to be outputted to screen as a 2-D vector of
    // characters with the same area as the terminal window
    int screen_rows, screen_cols;
    getmaxyx(stdscr, screen_rows, screen_cols);
    Frame frame(screen_rows);
    for (int i=0; i<screen_rows; i++) {
        frame[i].resize(screen_cols);
    }

    // Player
    Player player;
    player.y = 12;
    player.x = 4;
    player.angle = 0;
    double fov = M_PI / 3.0;
    double walk_speed = 50;
    double turn_speed = 75;

    // Map
    int map_y = 16;
    int map_x = 16;
    double render_dist = 20;

    wstring map;
	map += L"################";
	map += L"#########.......";
	map += L"#...............";
	map += L"#.......########";
	map += L"#..............#";
	map += L"#......##......#";
	map += L"#......##......#";
	map += L"#..............#";
	map += L"###............#";
	map += L"##.............#";
	map += L"#......####..###";
	map += L"#......#.......#";
	map += L"#......#.......#";
	map += L"#..............#";
	map += L"#......#########";
	map += L"#..............#";
	map += L"################";

    int ch = 0;
    double ray_angle, dist;
    int test_y, test_x;
    int floor, ceiling;
    auto prev = system_clock::now();
    auto cur = system_clock::now();
    double delta_sec;
    double step_y, step_x;
    short shade;
    while (true) {
        // Make game run at same pace regardless of processor speed or load
        cur = system_clock::now();
        duration<double> delta = cur - prev;
        delta_sec = delta.count();
        prev = cur;

        if ((ch = getch()) != ERR) {
            switch (ch) {
                case KEY_LEFT:
                    player.angle -= turn_speed * delta_sec;

                    break;

                case KEY_RIGHT:
                    player.angle += turn_speed * delta_sec; 

                    break;

                case KEY_UP:
                    step_y = walk_speed * cos(player.angle) * delta_sec;
                    step_x = walk_speed * sin(player.angle) * delta_sec;

                    if (map_at(map, map_y, map_x, player.y+step_y, player.x+step_x) != '#') {
                        player.y += step_y;
                        player.x += step_x;
                    }

                    break;

                case KEY_DOWN:
                    step_y = walk_speed * cos(player.angle) * delta_sec;
                    step_x = walk_speed * sin(player.angle) * delta_sec;

                    if (map_at(map, map_y, map_x, player.y-step_y, player.x-step_x) != '#') {
                        player.y -= step_y;
                        player.x -= step_x;
                    }

                    break;
            }
        }

        // Render frame
        for (int col=0; col<screen_cols; col++) {
            // Begin casting rays at left of view, casting one ray for each
            // column in the screen
            ray_angle = (player.angle - fov/2.0) +
                ((double)col / (double)screen_cols) * fov;

            // Calculate distance from player to wall (or edge of map) for this
            // ray
            dist = 0.0;
            do {
                dist += 0.1;

                test_y = player.y + cos(ray_angle) * dist;
                test_x = player.x + sin(ray_angle) * dist;
            } while (!hit_wall(map, map_y, map_x, test_y, test_x, dist,
                render_dist));

            // Determine floor and ceiling bounds
            ceiling = screen_rows / 2.0 - screen_rows / dist;
            floor = screen_rows - ceiling;

            // Fill this column with proper characters
            for (int row=0; row<screen_rows; row++) {
                if (row < ceiling) {
                    // Ceiling
                    frame[row][col] = ' ';
                } else if (row >= ceiling && row < floor) {
                    // Wall
                    if (dist <= render_dist / 4) {
                        shade = 0x2588;
                    } else if (dist <= render_dist / 3) {
                        shade = 0x2593;
                    } else if (dist <= render_dist / 2) {
                        shade = 0x2592;
                    } else if (dist <= render_dist) {
                        shade = 0x2591;
                    } else {
                        shade = ' ';
                    }

                    frame[row][col] = shade;
                } else {
                    // Floor
                    double floor_dist_factor = (double)(row - (screen_rows / 2)) / (double)(screen_rows / 2);
                    if (floor_dist_factor >= 0.75) {
                        shade = '#';
                    } else if (floor_dist_factor >= 0.4) {
                        shade = 'x';
                    } else if (floor_dist_factor >= 0.25) {
                        shade = '-';
                    } else if (floor_dist_factor >= 0.1) {
                        shade = '.';
                    } else {
                        shade = ' ';
                    }

                    frame[row][col] = shade;
                }
            }
        }

        display_frame(frame);
    }

    curs_set(1);
    endwin();

    return 0;
}
