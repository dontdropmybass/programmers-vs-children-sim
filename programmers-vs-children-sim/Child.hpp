//
//  Child.hpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-07.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#ifndef Child_hpp
#define Child_hpp

#include <stdio.h>
#include "Human.hpp"
#include "Programmer.hpp"

class Child : public Human {
public:
    int convert;
    Child(int x, int y);
    void move(int x, int y);
    int getXPos();
    int getYPos();
    int getSince();
    void setSince();
    void incSince();
};

#endif /* Child_hpp */
