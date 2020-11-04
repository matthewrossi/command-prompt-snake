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

#ifndef SNAKE_H
#define SNAKE_H

#include "controls.h"

struct Elem {
    int x, y;
    char piece;
    Elem *next;
};

class Snake {
    static const char kHorizontal = 196;
    static const char kHighLeftCorner = 218;
    static const char kHighRightCorner = 191;
    static const char kLowLeftCorner = 192;
    static const char kLowRightCorner = 217;
    static const char kVertical = 179;

    Elem *head, *tail;

    void enqueue(Elem *&);
    Elem *dequeue();

   public:
    int x, y;

    Snake();
    void create(int, int, int);
    void move(Direction &, Direction &);
    bool collision(Direction);
    bool collision(int, int);
    void flash(int, int);
    void eat();
    ~Snake();
};

#endif // SNAKE_H
