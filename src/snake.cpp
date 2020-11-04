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

#include "snake.h"

#include <windows.h>

#include <iostream>

#include "utils.h"

Snake::Snake() { head = tail = NULL; }

void Snake::enqueue(Elem *&node) {
    if (!(node = new Elem)) {
        throw std::bad_alloc();
    }
    if (!head)
        head = node;
    if (tail)
        tail->next = node;
    node->next = NULL;
    tail = node;
}

Elem *Snake::dequeue() {
    Elem *node = head;
    if (head) {
        head = head->next;
        if (!head)
            tail = NULL;
    }
    return node;
}

void Snake::create(int x, int y, int n) {
    Elem *node;
    this->x = x;
    this->y = y;

    // head of the queue = tail of the snake
    for (int i = n - 1; i >= 0; i--) {
        enqueue(node);
        node->x = x + i;
        node->y = y;
        node->piece = kHorizontal;
        gotoxy(x + i, y);
        std::cout << kHorizontal;
    }
}

void Snake::move(Direction &prev, Direction &curr) {
    // overwrite snake tail
    gotoxy(head->x, head->y);
    std::cout << ' ';
    delete dequeue();

    // ensure the snake cannot go backwards
    if ((prev == Direction::Up && curr == Direction::Down) ||
        (prev == Direction::Left && curr == Direction::Right) ||
        (prev == Direction::Down && curr == Direction::Up) ||
        (prev == Direction::Right && curr == Direction::Left))
        curr = prev;

    // create snake head element
    Elem *node;
    enqueue(node);

    // update snake head piece
    if (prev == Direction::Up && curr == Direction::Up ||
        prev == Direction::Down && curr == Direction::Down)
        node->piece = kVertical;
    else if (prev == Direction::Left && curr == Direction::Left ||
             prev == Direction::Right && curr == Direction::Right)
        node->piece = kHorizontal;
    else if (prev == Direction::Left && curr == Direction::Up ||
             prev == Direction::Down && curr == Direction::Right)
        node->piece = kLowLeftCorner;
    else if (prev == Direction::Down && curr == Direction::Left ||
             prev == Direction::Right && curr == Direction::Up)
        node->piece = kLowRightCorner;
    else if (prev == Direction::Up && curr == Direction::Right ||
             prev == Direction::Left && curr == Direction::Down)
        node->piece = kHighLeftCorner;
    else
        node->piece = kHighRightCorner;

    // update snake head position
    if (prev == Direction::Up)
        y--;
    else if (prev == Direction::Left)
        x--;
    else if (prev == Direction::Down)
        y++;
    else
        x++;
    
    node->x = x;
    node->y = y;

    // write snake head piece to screen
    gotoxy(x, y);
    std::cout << node->piece;

    prev = curr;
}

/// self-collision
bool Snake::collision(Direction dir) {
    Elem *iter = head;
    while (iter = iter->next)
        if (tail->y == iter->y + 1 && tail->x == iter->x &&
                dir == Direction::Up ||
            tail->x == iter->x + 1 && tail->y == iter->y &&
                dir == Direction::Left ||
            tail->y == iter->y - 1 && tail->x == iter->x &&
                dir == Direction::Down ||
            tail->x == iter->x - 1 && tail->y == iter->y &&
                dir == Direction::Right)
            return 1;
    return 0;
}

/// bonus generation collision
bool Snake::collision(int x, int y) {
    Elem *iter = head;
    while (iter = iter->next)
        if (x == iter->x && y == iter->y)
            return 1;
    return 0;
}

/// flashes the snake a given number of times
void Snake::flash(int num_times, int delay) {
    Elem *iter;
    for (; num_times; num_times--) {
        iter = head;
        while (iter) {
            gotoxy(iter->x, iter->y);
            std::cout << ' ';
            iter = iter->next;
        }
        Sleep(delay);
        iter = head;
        while (iter) {
            gotoxy(iter->x, iter->y);
            std::cout << iter->piece;
            iter = iter->next;
        }
        Sleep(delay);
    }
}

void Snake::eat() {
    Elem *node;
    enqueue(node);
    node->x = x;
    node->y = y;
    // node->piece=
}

Snake::~Snake() {
    while (head)
        delete dequeue();
}
