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

#include "bonus.h"

#include <windows.h>

#include <ctime>
#include <iostream>

#include "utils.h"

Bonus::Bonus(char face) { this->face = face; }

void Bonus::create(Snake &s, Level l) {
    // TODO: add window dimensions as constants
    // TODO: might become a problem as the available spots get lower and lower
    srand(time(NULL));
    do {
        // window dimensions (0-based)
        x = rand() % 79;    // 0 to 78
        y = rand() % 48;    // 0 to 47
    } while (s.collision(x, y) || l.collision(x, y));
    gotoxy(x, y);
    std::cout << face;
}

bool Bonus::collision(int xs, int ys) {
    if (xs == x && ys == y)
        return 1;
    return 0;
}
