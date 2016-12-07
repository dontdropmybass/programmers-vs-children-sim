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
}

void Child::move(int x, int y) {
    this->xpos = x;
    this->ypos = y;
}

int Child::getXPos() {
    return this->xpos;
}

int Child::getYPos() {
    return this->ypos;
}
