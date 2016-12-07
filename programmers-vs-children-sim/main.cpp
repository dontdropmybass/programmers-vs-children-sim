//
//  main.cpp
//  programmers-vs-children-sim
//
//  Created by Alexander Cochrane on 2016-12-05.
//  Copyright © 2016 Alexander Cochrane. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "GameSpecs.h"
#include "Human.hpp"
#include "Child.hpp"
#include "Programmer.hpp"

void clear() {
    for (int n = 0; n < 10; n++) printf( "\n\n\n\n\n\n\n\n\n\n" );
}

void childTurn(std::vector<Human*> * city) {
    std::cout<<"childTurn"<<std::endl;
}

void programmerTurn(std::vector<Human*> * city) {
    std::cout<<"programmerTurn"<<std::endl;
}

void printCity(std::vector<Human*> * city) {
//    for (int i = 0; i < city->size(); i++) {
//        if (i%GRIDSIZE) printf("|\n-----------------------------------------\n");
//        printf("|");
//        
//        if (dynamic_cast<Child*>(city->at(i))) {
//            std::cout<<((char)CHILD_CH);
//        }
//        
//        else if (dynamic_cast<Programmer*>(city->at(i))) {
//            std::cout<<((char)PROGRAMMER_CH);
//        }
//        
//        else {
//            std::cout<<((char)SPACE_CH);
//        }
//    }
    
    for (int i = 0; i < GRIDSIZE; i++) printf("--");
    printf("-\n");
    for (int x = 0; x < GRIDSIZE; x++) {
        for (int y = 0; y < GRIDSIZE; y++) {
            char c = (char) SPACE_CH;
            for (int i = 0; i < city->size(); i++) {
                if (city->at(i)->getXPos()==x&&city->at(i)->getYPos()==y) {
                    if (dynamic_cast<Child*>(city->at(i))) {
                        c = (char) CHILD_CH;
                    }
                    else if (dynamic_cast<Programmer*>(city->at(i))) {
                        c = (char) PROGRAMMER_CH;
                    }
                }
            }
            printf("|");
            std::cout << c;
        }
        printf("|\n");
        for (int i = 0; i < GRIDSIZE; i++) printf("--");
        printf("-\n");
    }
}

int main() {
//    Human* city[GRIDSIZE*GRIDSIZE];
    std::vector<Human*> city;
    
    int numChildren = 0;
    int numProgrammers = 0;
    
    while (numChildren < CHILD_STARTCOUNT) {
        bool b = true;
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;
        for (int i = 0; i < city.size(); i++) {
            Human* human = city.at(i);
            if (human->getXPos()==x&&human->getYPos()==y) b = false;
        }
        if (b) {
            Child* child = new Child(x,y);
            city.push_back(child);
            numChildren++;
        }
    }
    
    while (numProgrammers < PROGRAMMER_STARTCOUNT) {
        bool b = true;
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;
        for (int i = 0; i < city.size(); i++) {
            Human* human = city.at(i);
            if (human->getXPos()==x&&human->getYPos()==y) b = false;
        }
        if (b) {
            Programmer* programmer = new Programmer(x,y);
            city.push_back(programmer);
            numProgrammers++;
        }
    }
    
    for (int i = 0; i < ITERATIONS; i++) {
        childTurn(&city);
        programmerTurn(&city);
        printCity(&city);
        usleep(1000*PAUSE_MICROSECONDS);
        clear();
    }
    
    return 0;
}
