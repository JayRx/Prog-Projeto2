
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "colorfunctions.h"

using namespace std;

void gotoxy(int x, int y)
{
    ostringstream oss;
    oss << "\033[" << y << ";" << x << "H";
    cout << oss.str();
}

void clrscr(int x, int y)
{
    cout << "\033[2J";
    gotoxy(x,y);
}

void setcolor(string color)
{
    cout << color;
}

void setcolor(string color, string backcolor)
{
    cout << color << backcolor;
}

