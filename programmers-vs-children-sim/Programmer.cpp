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
}

void Programmer::move(int x, int y) {
    this->xpos = x;
    this->ypos = y;
}

int Programmer::getXPos() {
    return this->xpos;
}

int Programmer::getYPos() {
    return this->ypos;
}
