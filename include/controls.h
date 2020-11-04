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

#ifndef CONTROLS_H
#define CONTROLS_H

#include <string>

const unsigned int kNumControls = 6;
const unsigned int kNumDirections = 4;

enum class Control { Up, Left, Down, Right, Pause, Escape };
enum class Direction { Up, Left, Down, Right };

class Controls {
    char buttons[kNumControls + 1];
   public:
    static const std::string kDescriptions[];

    Controls(char[]);
    void setControl(Control, char);
    bool toDirection(char, Direction &);
    bool isPause(char);
    bool isEscape(char);
};

#endif // CONTROLS_H
