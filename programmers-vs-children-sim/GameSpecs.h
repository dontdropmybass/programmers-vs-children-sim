#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid
const int CHILD_STARTCOUNT = 100; // inital Child count
const int PROGRAMMER_STARTCOUNT = 5; //initial Programmer count
const int HUMAN_BREED = 3; // steps until a Child duplicates
const int ZOMBIE_BREED = 8; // steps until an Programmer duplicates
const int ZOMBIE_STARVE = 3; // steps until a Programmer gets fired and reverts to a Child
const char CHILD_CH = 67; // ascii `C` for Child
const char SPACE_CH = 32; // " " ascii space
const char PROGRAMMER_CH = 80;// ascii `P` for Programmer
const double PAUSE_MICROSECONDS = 90000; // pause between steps
const int ITERATIONS = 1000; // max number of steps

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int CHILD_COLOR = 13;  // bright pink
const int PROGRAMMER_COLOR = 10; // bright green

#endif
