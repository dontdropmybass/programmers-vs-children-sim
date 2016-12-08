//
//  Child.cpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-07.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#include "Child.hpp"

Child::Child(int x, int y) {
    this->xpos = x;
    this->ypos = y;
    this->since = 0;
    this->convert = 0;
}

// move the number of spaces in whatever direction it tells you
void Child::move(int x, int y) {
    this->xpos += x;
    this->ypos += y;
}

int Child::getXPos() {
    return this->xpos;
}

int Child::getYPos() {
    return this->ypos;
}

// get how long it's been since you've had a child
int Child::getSince() {
    return this->since;
}

// reset the teen mom counter to 0
void Child::setSince() {
    this->since = 0;
}

// add 1 to the teen mom counter
void Child::incSince() {
    this->since++;
}
