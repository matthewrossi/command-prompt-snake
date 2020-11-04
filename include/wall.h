/*
 * Copyright (c) 2020 Matthew Rossi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef WALL_H
#define WALL_H

#include "controls.h"

class Wall {
    static const char kBlock = 219;
    static const char kHighLeftCorner = 201;
    static const char kHighRightCorner = 187;
    static const char kHorizontal = 205;
    static const char kLowLeftCorner = 200;
    static const char kLowRightCorner = 188;
    static const char kVertical = 186;

    // TODO: use coordinates w/ better naming
    int x, y, x1, y1;
    bool inside;

   public:
    Wall();
    Wall(int, int, int, int, bool);

    void draw();
    bool collision(int, int, Direction);
    bool collision(int, int);
};

#endif // WALL_H
