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

Child* checkIfChild(int x, int y, std::vector<Human*> * city) {
    for (Human* human : *city) {
        if (human->getXPos()==x&&human->getYPos()==y) {
            if (dynamic_cast<Child*>(human)) {
                return dynamic_cast<Child*>(human);
            }
        }
    }
    return NULL;
}

void childTurn(std::vector<Human*> * city) {
    std::cout<<"childTurn"<<std::endl;
    for (Human* human : *city) {
        if (!dynamic_cast<Child*>(human)) {
            continue;
        }
        bool b = true;
        int x = 0;
        int y = 0;
        int tries = 0;
        // try to move
        while (b && tries < 100) {
            tries++;
            x = rand() % 3 - 1;
            if (x) y = 0;
            else y = rand() % 3 - 1;
            for (Human* subhuman : *city) {
                if (human->getXPos()+x != subhuman->getXPos() || human->getYPos()+y != subhuman->getYPos()) {
                    b = false;
                }
                if (human->getXPos()+x >= GRIDSIZE || human->getYPos()+y >= GRIDSIZE) {
                    b = true;
                }
            }
        }
        if (!b) human->move(x,y);
        
        // if you've lived for at least 3 turns, have a teen baby
        if (human->getSince()>=CHILD_TEENMOM) {
            human->setSince();
            for (x = -1; x <= 1; x++) {
                for (y = -1; y <= 1; y++) {
                    for (Human* subhuman : *city) {
                        if (subhuman->getXPos()!=human->getXPos()+x ||
                            subhuman->getYPos()!=human->getYPos()+y) {
                            Child* child = new Child(human->getXPos()+x,human->getYPos()+y);
                            city->insert(city->begin(), child);
                            goto ok;
                        }
                    }
                }
            }
        }
        else {
            human->incSince();
        }
    ok:
        int sadfghooiugfhchvjbjiouiytcgvhjbj = 0;
    }
}

void programmerTurn(std::vector<Human*> * city) {
    std::cout<<"programmerTurn"<<std::endl;
    for (Human* human : *city) {
        if (!dynamic_cast<Programmer*>(human)) {
            continue;
        }
        human->incSince();
        bool b = true;
        int x = 0;
        int y = 0;
        int tries = 0;
        // try to eat a child
        for (x = -1; x <= 1; x++) {
            for (y = -1; y <= 1; y++) {
                if (checkIfChild(human->getXPos()+x, human->getYPos()+y, city) != NULL) {
                    Child* child = checkIfChild(human->getXPos()+x, human->getYPos()+y, city);
                    auto it = std::find(city->begin(), city->end(), child);
                    if (it != city->end()) city->erase(it);
                    b = false;
                    human->setSince();
                    goto s;
                }
            }
        }
    s:
        // otherwise find an empty spot to move into
        while (b && tries < 100) {
            tries++;
            x = rand() % 3 - 1;
            if (x) y = 0;
            else y = rand() % 3 - 1;
            for (Human* subhuman : *city) {
                if (human->getXPos()+x != subhuman->getXPos() || human->getYPos()+y != subhuman->getYPos()) {
                    b = false;
                }
                if (human->getXPos()+x >= GRIDSIZE || human->getYPos()+y >= GRIDSIZE) {
                    b = true;
                }
            }
        }
        // move into the empty spot
        if (!b) {
            human->move(x,y);
        }
        // if you haven't been turned back into a child yet, turn a nearby child into a programmer
        if (human->convert!=0 && human->convert%PROGRAMMER_CONVERT==0) {
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (checkIfChild(human->getXPos()+x, human->getYPos()+y, city) != NULL) {
                        Child* child = checkIfChild(human->getXPos()+x, human->getYPos()+y, city);
                        Programmer* programmer = new Programmer(child->getXPos(),child->getYPos());
                        auto it = std::find(city->begin(), city->end(), child);
                        if (it != city->end()) city->erase(it);
                        city->insert(city->begin(), programmer);
                        human->convert = 0;
                        goto lol;
                    }
                }
            }
        }
        else {
            human->convert++;
        }
    lol:
        // if you haven't eaten any children in a while, lose your job and become a child
        if (human->getSince()>=PROGRAMMER_LOSEJOB) {
            Child* child = new Child(human->getXPos(), human->getYPos());
            auto it = std::find(city->begin(), city->end(), human);
            if (it != city->end()) city->erase(it);
            city->insert(city->begin(), child);
        }
    }
}

void printCity(std::vector<Human*> * city) {
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
        programmerTurn(&city);
        childTurn(&city);
        printCity(&city);
        usleep(/*1000**/PAUSE_MICROSECONDS);
        clear();
    }
    
    return 0;
}
