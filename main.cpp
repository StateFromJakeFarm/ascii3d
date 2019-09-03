#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>
#include <iostream>
#include <ctime>
#include "game_map.h"
#include "player.h"
#include "frame.h"

using std::vector;
using std::string;
using std::chrono::system_clock;
using std::chrono::duration;
using std::cout;
using std::endl;

void draw(const Frame &frame) {
    move(0, 0);
    for (auto &row : frame.picture) {
        addwstr(row);
    }

    wrefresh(stdscr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "USAGE: game <map file>" << endl;
        return 1;
    }

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

    // Map
    string map_file = argv[1];
    GameMap game_map(map_file);

    // Player
    double p_y = 4;
    double p_x = 4;
    double p_view_angle = 0;
    double fov = M_PI / 3.0;
    double walk_speed = 0.1;
    double turn_speed = 0.2;
    Player player(&game_map, p_y, p_x, p_view_angle, fov, walk_speed, turn_speed);

    // Frame
    int render_dist = 15;
    double corner_resolution = 0.1;
    int frame_rate = 60;
    double frame_period = 1 / (double)frame_rate;
    Frame frame(&game_map, &player, screen_rows, screen_cols, render_dist, corner_resolution);

    int ch = 0;
    auto prev = system_clock::now();
    auto cur = system_clock::now();
    double frame_duration;
    while (true) {
        // Make game run at same pace regardless of processor speed or load
        cur = system_clock::now();
        duration<double> delta = cur - prev;
        frame_duration = delta.count();
        prev = cur;

        if ((ch = getch()) != ERR) {
            switch (ch) {
                case KEY_RIGHT:
                    player.turn_right();
                    break;

                case KEY_LEFT:
                    player.turn_left();
                    break;

                case 'w':
                    player.walk_forward();
                    break;

                case 's':
                    player.walk_backward();
                    break;

                case 'd':
                    player.strafe_right();
                    break;

                case 'a':
                    player.strafe_left();
                    break;
            }
        }

        frame.render();
        draw(frame);

        // If necessary, wait enough time to ensure desired frame rate
        if (frame_duration < frame_period) {
            sleep(frame_period - frame_duration);
        }
    }

    curs_set(1);
    endwin();

    return 0;
}
