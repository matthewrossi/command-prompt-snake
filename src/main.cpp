// Copyright (c) 2020 Matthew Rossi
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "bar.h"
#include "bonus.h"
#include "controls.h"
#include "level.h"
#include "snake.h"
#include "utils.h"
#include "wall.h"

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>

int to_ms(int speed) {
    return 50 + (10 - speed) * 20;
}

int main() {
    set_cursor_visibility(FALSE);
    window_size(79, 48);
    system("title Snake");
    system("color F0");

    char menu;
    int speed = 5;
    int sleep = to_ms(speed);
    Controls ctrls("WASDP\x1B"); // 1B hex = 27 dec = ESC

    do {
        system("cls");

        scw(10, "MAIN MENU");
        scw(14, "1. Play");
        scw(16, "2. Configure starting speed");
        scw(18, "3. Configure keybindings");
        scw(40, "4. EXIT");

        menu = _getch();
        system("cls");

        switch (menu) {
            // Play
            case '1': {
                char answer;
                // consider loading level configuration from file
                Wall walls[] = {
                    Wall(0, 1, 79, 48, true), Wall(10, 10, 10, 20, false),
                    Wall(30, 30, 30, 30, false), Wall(60, 30, 70, 45, false),
                    Wall(10, 20, 30, 20, false)};
                Level level(walls, 5);
                Bonus food(254);

                do {
                    answer = 'N';

                    bool collision = false;
                    char button;
                    int points = 0;  // consider moving this into the level
                                     // with a text class
                    Snake ekans;
                    Direction prev_direction = Direction::Left;
                    Direction curr_direction = Direction::Left;

                    std::cout << "Points " << points;
                    level.draw();
                    ekans.create(38, 25, 10);
                    food.create(ekans, level);

                    do {
                        do {
                            ekans.move(prev_direction, curr_direction);
                            if (food.collision(ekans.x, ekans.y)) {
                                points++;
                                gotoxy(7, 0);
                                std::cout << points;
                                ekans.eat();
                                food.create(ekans, level);
                            }
                            Sleep(sleep -
                                  points * 5);  // consider changing this
                        } while (
                            !kbhit() && !ekans.collision(curr_direction) &&
                            !level.collision(ekans.x, ekans.y, curr_direction));

                        if (!ekans.collision(curr_direction) &&
                            !level.collision(ekans.x, ekans.y, curr_direction))
                            // exit loop due to button press
                            // TODO: ensure it gets the last valid control to
                            //       improve responsiveness when hard spamming
                            button = toupper(_getch());
                        else
                            collision = true;

                        if (ctrls.isPause(button)) {
                            gotoxy(37, 0);
                            std::cout << "Pause";
                            // flush input buffer to avoid skipping the pause
                            // due to previous input
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            _getch();   // press any button to continue
                            gotoxy(37, 0);
                            std::cout << "     ";
                        }
                        ctrls.toDirection(button, curr_direction);
                    } while (!ctrls.isEscape(button) && !collision);

                    if (!ctrls.isEscape(button)) {
                        ekans.flash(5, 150);
                        scw(18, "GAME OVER");
                        scw(20, "Points: " + std::to_string(points));
                        Sleep(350);
                        scw(25, " Restart? (Y/N)");
                        do {
                            answer = toupper(_getch());
                        } while (answer != 'Y' && answer != 'N' && answer != kEsc);
                    }
                    system("cls");
                } while (answer == 'Y');
                break;
            }

            // Change starting speed
            case '2': {
                // TODO: save this to configuration file
                char button;
                Bar bar(33, 21, 10, speed);
                
                scw(18, "Starting speed");
                bar.draw();
                cw(24, "Left [Left Arrow]   Right [Right Arrow]   Select [Enter]");

                do {
                    button = getch();
                    bar.chgValue(button);
                } while (button != kEnter && button != kEsc);

                speed = bar.getValue();
                sleep = to_ms(speed);

                system("cls");
                break;
            }

            // Change keybindings
            case '3':
                // TODO: save this to configuration file
                for (int i = 0; i < kNumControls; i++) {
                    scw(25, "Button " + ctrls.kDescriptions[i]);
                    ctrls.setControl((Control)i, toupper(_getch()));
                }
                system("cls");
                break;
        }
    } while (menu != '4' && menu != kEsc);
    // TODO: restore previous command prompt state
    set_cursor_visibility(TRUE);
    return EXIT_SUCCESS;
}
