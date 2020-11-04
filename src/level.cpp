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

#include "level.h"

Level::Level(Wall walls[], int n) {
    this->walls = walls;
    nWalls = n;
}

void Level::draw() {
    for (int i = 0; i < nWalls; i++)
        walls[i].draw();
}

/// snake collision with level assets
bool Level::collision(int x, int y, Direction dir) {
    for (int i = 0; i < nWalls; i++)
        if (walls[i].collision(x, y, dir))
            return 1;
    return 0;
}

/// bonus generation collision
bool Level::collision(int x, int y) {
    for (int i = 0; i < nWalls; i++)
        if (walls[i].collision(x, y))
            return 1;
    return 0;
}
