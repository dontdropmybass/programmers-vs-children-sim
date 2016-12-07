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

class Child : public Human {
public:
    Child(int x, int y);
    void move(int x, int y);
    int getXPos();
    int getYPos();
};

#endif /* Child_hpp */
