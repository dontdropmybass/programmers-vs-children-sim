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
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include "GameSpecs.h"
#include "Human.hpp"
#include "Child.hpp"
#include "Programmer.hpp"

#define _getch() std::system("read -n1 -p 'Press any key...\n' key");
// clears the screen
void clear() {
    for (int n = 0; n < 10; n++) printf( "\n\n\n\n\n\n\n\n\n\n" );
}

// asks all humans in city if they're children, and if they're in the position (X,Y)
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

// let the children do what they're supposed to
void childTurn(std::vector<Human*> * city) {
    std::vector<Human*> city2;
    for (Human* human : *city) {
        city2.push_back(human);
    }
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
                // make sure the movement won't be outside the city
                if (human->getXPos()+x >= GRIDSIZE || human->getYPos()+y >= GRIDSIZE ||
                    human->getXPos()+x < 0 || human->getYPos()+y < 0) {
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
                            // make sure the child won't be born outside the city
                            if (human->getXPos()+x >= GRIDSIZE || human->getYPos()+y >= GRIDSIZE ||
                                human->getXPos()+x < 0 || human->getYPos()+y < 0) {
                                goto ok;
                            }
                            Child* child = new Child(human->getXPos()+x,human->getYPos()+y);
                            city2.insert(city2.begin(), child);
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
        int sadfghooiugfhchvjbjiouiytcgvhjbj = 0; // FIXME: horrible hack
    }
    city->clear();
    for (Human* human : city2) {
        city->push_back(human);
    }
}

// let the zombies do what they're supposed to
void programmerTurn(std::vector<Human*> * city) {
    std::vector<Human*> city2;
    for (Human* human : *city) {
        city2.push_back(human);
    }
    for (Human* human : *city) {
        if (!dynamic_cast<Programmer*>(human)) {
            continue;
        }
        human->incSince();
        bool b = true;
        int x = 0;
        int y = 0;
        int tries = 0;
        // try to make a child cry
        for (x = -1; x <= 1; x++) {
            for (y = -1; y <= 1; y++) {
                if (checkIfChild(human->getXPos()+x, human->getYPos()+y, city) != NULL) {
                    Child* child = checkIfChild(human->getXPos()+x, human->getYPos()+y, city);
                    auto it = std::find(city2.begin(), city2.end(), child);
                    if (it != city2.end()) city2.erase(it);
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
                // make sure that spot isn't outside the city
                if (human->getXPos()+x >= GRIDSIZE || human->getYPos()+y >= GRIDSIZE ||
                    human->getXPos()+x < 0 || human->getYPos()+y < 0) {
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
                        auto it = std::find(city2.begin(), city2.end(), child);
                        if (it != city2.end()) city2.erase(it);
                        city2.insert(city2.begin(), programmer);
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
            auto it = std::find(city2.begin(), city2.end(), human);
            if (it != city2.end()) city2.erase(it);
            city2.insert(city2.begin(), child);
        }
    }
    city->clear();
    for (Human* human : city2) {
        city->push_back(human);
    }
}

// print the city grid
void printCity(std::vector<Human*> * city) {
    for (int i = 0; i < GRIDSIZE; i++) printf("--");
    printf("-\n");
    // for every x and y coordinate in the city, ask all humans if they're in that spot
    for (int x = 0; x < GRIDSIZE; x++) {
        for (int y = 0; y < GRIDSIZE; y++) {
            char c = (char) SPACE_CH;
            const char* color = DEFAULT_COLOR;
            for (int i = 0; i < city->size(); i++) {
                if (city->at(i)->getXPos()==x&&city->at(i)->getYPos()==y) {
                    // if it's a child, put the `C` character
                    if (dynamic_cast<Child*>(city->at(i))) {
                        c = (char) CHILD_CH;
                        color = CHILD_COLOR;
                    }
                    // if it's a programmer, put the `P` character
                    else if (dynamic_cast<Programmer*>(city->at(i))) {
                        c = (char) PROGRAMMER_CH;
                        color = PROGRAMMER_COLOR;
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
    std::vector<Human*> city;
    
    int numChildren = 0;
    int numProgrammers = 0;
    
    srand((int)time(NULL));
    
    // generate a bunch of children
    while (numChildren < CHILD_STARTCOUNT) {
        bool b = true;
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;
        for (int i = 0; i < city.size() && b; i++) {
            Human* human = city.at(i);
            if (human->getXPos()==x&&human->getYPos()==y) b = false;
        }
        if (b) {
            Child* child = new Child(x,y);
            city.push_back(child);
            numChildren++;
        }
    }
    
    // generator a bunch of programmers
    while (numProgrammers < PROGRAMMER_STARTCOUNT) {
        bool b = true;
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;
        for (int i = 0; i < city.size() && b; i++) {
            Human* human = city.at(i);
            if (human->getXPos()==x&&human->getYPos()==y) b = false;
        }
        if (b) {
            Programmer* programmer = new Programmer(x,y);
            city.push_back(programmer);
            numProgrammers++;
        }
    }
    
    // for the length of the game, do turns
    for (int i = 0; i < ITERATIONS; i++) {
        programmerTurn(&city);
        childTurn(&city);
        printCity(&city);
        numProgrammers = 0;
        numChildren = 0;
        for (Human* human : city) {
            if (dynamic_cast<Programmer*>(human)) {
                numProgrammers++;
            }
            else if (dynamic_cast<Child*>(human)) {
                numChildren++;
            }
        }
        std::cout << "Turn: " << i+1 << std::endl;
        std::cout << "Programmers: " << numProgrammers << std::endl;
        std::cout << "Children: " << numChildren << std::endl;
        usleep(PAUSE_MICROSECONDS);
        clear();
        // see if the game's over:
        if (numChildren + numProgrammers >= GRIDSIZE*GRIDSIZE) {
            printf("All these people caused global warming.\nThe ice caps melted and drowned everybody.\nI hope you're happy. Game over.\n");
            goto end;
        }
        else if (numChildren || numProgrammers) {
            if (!numChildren) {
                printf("Programmers have converted all children into programmers. Game over.\n");
                goto end;
            }
            else if (!numProgrammers) {
                printf("All programmers have reverted to child state. Game over.\n");
                goto end;
            }
        }
        else {
            printf("Everybody's dead, you killed them, didn't you?\n");
            goto end;
        }
        
    }
    std::cout << ITERATIONS << " turns have passed and there is no winner. Game over." << std::endl;
end:
    _getch();
    
    return 0;
}
