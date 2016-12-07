//
//  Human.hpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-07.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp

#include <stdio.h>

class Human {
protected:
    int xpos;
    int ypos;
    int since;
public:
    Human();
    int convert;
    virtual void move(int x, int y) = 0;
    virtual int getXPos() = 0;
    virtual int getYPos() = 0;
    virtual int getSince() = 0;
    virtual void setSince() = 0;
    virtual void incSince() = 0;
};

#endif /* Human_hpp */
