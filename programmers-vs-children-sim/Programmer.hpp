//
//  Programmer.hpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-07.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#ifndef Programmer_hpp
#define Programmer_hpp

#include <stdio.h>
#include "Human.hpp"
#include "Child.hpp"

class Programmer : public Human {
public:
    int convert;
    Programmer(int x, int y);
    void move(int x, int y);
    int getXPos();
    int getYPos();
    int getSince();
    void setSince();
    void incSince();
};

#endif /* Programmer_hpp */
