#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>
#include <iostream>
#include "game_map.h"
#include "player.h"
#include "frame.h"

using std::vector;
using std::string;
using std::wstring;
using std::chrono::system_clock;
using std::chrono::duration;
using std::cout;
using std::endl;

void draw(const Frame &frame) {
    move(0, 0);
    for (int r=0; r<frame.screen_rows; r++) {
        wstring line;
        for (int c=0; c<frame.screen_cols; c++) {
            line += frame.picture[r][c];
        }
        addwstr(line.c_str());
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

    // Player
    double p_y = 4;
    double p_x = 4;
    double p_view_angle = 0;
    double fov = M_PI / 3.0;
    double walk_speed = 30;
    double turn_speed = 50;
    Player player(p_y, p_x, p_view_angle, fov, walk_speed, turn_speed);

    // Map
    string map_file = argv[1];
    GameMap game_map(map_file);

    // Frame
    int render_dist = 15;
    Frame frame(&game_map, &player, screen_rows, screen_cols, render_dist);

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
                    player.turn_right(frame_duration);
                    break;

                case KEY_LEFT:
                    player.turn_left(frame_duration);
                    break;

                case 'w':
                    player.walk_forward(game_map, frame_duration);
                    break;

                case 's':
                    player.walk_backward(game_map, frame_duration);
                    break;

                case 'd':
                    player.strafe_right(game_map, frame_duration);
                    break;

                case 'a':
                    player.strafe_left(game_map, frame_duration);
                    break;
            }
        }

        frame.render();
        draw(frame);
    }

    curs_set(1);
    endwin();

    return 0;
}
