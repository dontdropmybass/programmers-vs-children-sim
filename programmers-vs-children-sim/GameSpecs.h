#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid DEFAULT 20
const int CHILD_STARTCOUNT = 50; // inital Child count DEFAULT 100
const int PROGRAMMER_STARTCOUNT = 5; //initial Programmer count DEFAULT 5
const int CHILD_TEENMOM = 18; // steps until a Child duplicates DEFAULT 3
const int PROGRAMMER_CONVERT = 7; // steps until an Programmer hires a child DEFAULT 8
const int PROGRAMMER_LOSEJOB = 10; // steps until a Programmer gets fired and reverts to a Child DEFAULT 3
const char CHILD_CH = 67; // ascii character for Child DEFAULT 67 = `C`
const char SPACE_CH = 32; // ascii empty square character DEFAULT 32 = ` `
const char PROGRAMMER_CH = 80;// ascii character for Programmer DEFAULT 80 = `P`
const double PAUSE_MICROSECONDS = 90000; // pause between steps in microseconds DEFAULT 90000
const int ITERATIONS = 1000; // max number of steps DEFAULT 1000

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

const char* CHILD_COLOR = "\033[13m";  // bright pink
const char* PROGRAMMER_COLOR = "\033[10m"; // bright green
const char* DEFAULT_COLOR = "\033[7m"; // white regular

#endif
