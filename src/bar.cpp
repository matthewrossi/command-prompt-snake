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

#include <windows.h>

#include <iostream>

#include "utils.h"

Bar::Bar(int x, int y, int size, int starting_value) {
    // TODO: add support to variable hights
    if (size <= 0) {
        throw std::invalid_argument("Expected positive bar size.");
    }
    if (starting_value < 0 || starting_value > size) {
        throw std::invalid_argument(
            "Starting value must be positive and not exceed the bar size.");
    }

    this->size = size;
    value = starting_value;
    this->x = x;
    this->y = y;
}

void Bar::draw() {
    // TODO: ensure the drawing is done within the current window boundaries
    char left = (value ? kLeftArrow : ' ');
    char right = (value < size ? kRightArrow : ' ');

    gotoxy(x + 1, y - 1);
    std::cout << kHighLeftCorner;
    for (int i = 0; i < size; i++)
        std::cout << kHorizontal;
    std::cout << kHighRightCorner;
    gotoxy(x + 1, y + 1);
    std::cout << kLowLeftCorner;
    for (int i = 0; i < size; i++)
        std::cout << kHorizontal;
    std::cout << kLowRightCorner;
    gotoxy(x, y);
    std::cout << left << kVertical;
    for (int i = 0; i < value; i++)
        std::cout << kBlock;
    gotoxy(x + size + 2, y);
    std::cout << kVertical << right;
}

void Bar::incValue() {
    if (value < size) {
        value++;
        gotoxy(x + value + 1, y);
        std::cout << kBlock;
        if (value == size) {
            gotoxy(x + size + 3, y);
            std::cout << ' ';
        } else if (value == 1) {
            gotoxy(x, y);
            std::cout << kLeftArrow;
        }
    }
}

void Bar::decValue() {
    if (value > 0) {
        value--;
        gotoxy(x + value + 2, y);
        std::cout << ' ';
        if (!value) {
            gotoxy(x, y);
            std::cout << ' ';
        } else if (value == size - 1) {
            gotoxy(x + size + 3, y);
            std::cout << kRightArrow;
        }
    }
}

void Bar::chgValue(char scelta) {
    // TODO: support direct number too
    if (scelta == kLeft)
        decValue();
    else if (scelta == kRight)
        incValue();
}

void Bar::flash() {
    // TODO: add timing varible to bar configuration
    Sleep(100);
    gotoxy(x, y);
    std::cout << ' ';
    gotoxy(x + size + 3, y);
    std::cout << ' ';
    Sleep(100);
    if (value > 0) {
        gotoxy(x, y);
        std::cout << kLeftArrow;
    }
    if (value < size) {
        gotoxy(x + size + 3, y);
        std::cout << kRightArrow;
    }
}

int Bar::getValue() { return value; }
