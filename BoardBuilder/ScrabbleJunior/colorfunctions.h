

#ifndef colorfunctions_h
#define colorfunctions_h

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y);

//Clear the screan
void clrscr(int x = 0, int y = 0);

//Set text color
void setcolor(string color);

//Set text color and background
void setcolor(string color, string background_color);

#endif /* colorfunctions_h */
