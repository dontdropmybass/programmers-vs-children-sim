//
//  Programmer.cpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-07.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#include "Programmer.hpp"

Programmer::Programmer(int x, int y) {
    this->xpos = x;
    this->ypos = y;
    this->since = 0;
    this->convert = 0;
}

// move the number of spaces in whatever direction it tells you
void Programmer::move(int x, int y) {
    this->xpos += x;
    this->ypos += y;
}

int Programmer::getXPos() {
    return this->xpos;
}

int Programmer::getYPos() {
    return this->ypos;
}

// see how long it's been since you've made a child cry
int Programmer::getSince() {
    return this->since;
}

// reset the make child cry counter to 0
void Programmer::setSince() {
    this->since = 0;
}

// add one to the make child cry counter
void Programmer::incSince() {
    this->since++;
}
