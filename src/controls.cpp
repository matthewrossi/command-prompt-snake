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

#include "controls.h"

#include <string.h>

#include <stdexcept>

const std::string Controls::kDescriptions[] = {"UP", "LEFT", "DOWN", "RIGHT",
                                               "PAUSE", "ESCAPE"};

Controls::Controls(char buttons[]) {
    if (strlen(buttons) != kNumControls) {
        throw std::invalid_argument(
            "arguments must be kNumControls elements long");
    }

    strncpy(this->buttons, buttons, kNumControls);
    this->buttons[kNumControls] = 0;
}

void Controls::setControl(Control ctrl, char button) {
    buttons[(int)ctrl] = button;
    for (int i = 0; i < (int)ctrl; i++) {
        if (buttons[i] == button)
            buttons[i] = 0; // consider setting it back to its original value
    }
}

bool Controls::toDirection(char button, Direction &dir) {
    char *ptr = strchr(buttons, button);
    if (ptr != NULL) {
        int idx = ptr - buttons;
        if (idx < kNumDirections) {
            dir = (Direction)idx;
            return true;
        }
    }
    return false;
}

bool Controls::isPause(char button) {
    return buttons[(int)Control::Pause] == button;
}

bool Controls::isEscape(char button) {
    return buttons[(int)Control::Escape] == button;
}
