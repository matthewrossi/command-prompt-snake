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

#include "wall.h"

#include <iostream>

#include "utils.h"

Wall::Wall(int x, int y, int x1, int y1, bool inside) {
    if (x > x1) std::swap(x, x1);
    if (y > y1) std::swap(y, y1);

    this->x = x;
    this->y = y;
    this->x1 = x1;
    this->y1 = y1;
    this->inside = inside;
}

void Wall::draw() {
    // TODO: ensure the drawing is done within the current window boundaries
    int i;
    if (x == x1 && y == y1) {
        // a point-like wall
        gotoxy(x, y);
        std::cout << kBlock;
    } else if (x == x1) {
        // a vertical wall
        for (i = y + 1; i <= y1 - 1; i++) {
            gotoxy(x, i);
            std::cout << kVertical;
        }
        gotoxy(x, y);
        std::cout << kBlock;
        gotoxy(x, y1);
        std::cout << kBlock;
    } else if (y == y1) {
        // an horizontal wall
        for (i = x + 1; i <= x1 - 1; i++) {
            gotoxy(i, y);
            std::cout << kHorizontal;
        }
        gotoxy(x, y);
        std::cout << kBlock;
        gotoxy(x1, y);
        std::cout << kBlock;
    } else {
        // a two-dimensional wall
        gotoxy(x, y);
        std::cout << kHighLeftCorner;
        gotoxy(x, y1);
        std::cout << kLowLeftCorner;
        gotoxy(x1, y);
        std::cout << kHighRightCorner;
        gotoxy(x1, y1);
        std::cout << kLowRightCorner;
        for (i = x + 1; i <= x1 - 1; i++) {
            gotoxy(i, y);
            std::cout << kHorizontal;
            gotoxy(i, y1);
            std::cout << kHorizontal;
        }
        for (i = y + 1; i <= y1 - 1; i++) {
            gotoxy(x, i);
            std::cout << kVertical;
            gotoxy(x1, i);
            std::cout << kVertical;
        }
    }
}

/// snake collision w/ wall
bool Wall::collision(int xs, int ys, Direction dir) {
    if (!inside &&
            (xs == x - 1 && ys >= y && ys <= y1 && dir == Direction::Right ||
             xs == x1 + 1 && ys >= y && ys <= y1 && dir == Direction::Left ||
             ys == y - 1 && xs >= x && xs <= x1 && dir == Direction::Down ||
             ys == y1 + 1 && xs >= x && xs <= x1 && dir == Direction::Up) ||
        inside &&
            (xs == x + 1 && ys >= y && ys <= y1 && dir == Direction::Left ||
             xs == x1 - 1 && ys >= y && ys <= y1 && dir == Direction::Right ||
             ys == y + 1 && xs >= x && xs <= x1 && dir == Direction::Up ||
             ys == y1 - 1 && xs >= x && xs <= x1 && dir == Direction::Down))
        return 1;
    return 0;
}

/// bonus generation collision
bool Wall::collision(int xb, int yb) {
    if (!inside && ((xb >= x && xb <= x1) && (yb >= y && yb <= y1)) ||
        inside && ((xb <= x || xb >= x1) || (yb <= y || yb >= y1)))
        return 1;
    return 0;
}
