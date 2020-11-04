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

#include "utils.h"

#include <windows.h>

#include <iostream>

void gotoxy(int x, int y) {
    COORD c = {(short) x, (short) y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cw(int y, std::string str) {
    gotoxy(40 - str.length() / 2, y);
    std::cout << str;
}

void scw(int y, std::string in, int t) {
    std::string out = "";
    for (int k = 0; k <= in.length(); k++) {
        cw(y, out);
        Sleep(t);
        out += in[k];
    }
}

void window_size(int x, int y) {
    SMALL_RECT sr = {0, 0, (short) x, (short) y};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &sr);
}

void set_cursor_visibility(bool visibile) {
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = visibile;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}
