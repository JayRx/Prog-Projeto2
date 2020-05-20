#include <stdio.h>
#include "cell.h"
#include <string>

using namespace std;


//Cell constructor
Cell::Cell()
{
    letter = ' ';
}

//--------------------------------------------
//Cell constructor with coordinates(line, col)
Cell::Cell(const size_t line, const size_t col)
{
    x = line;
    y = col;
    letter = ' ';
}

//--------------------------------------------
//Stores position of letter in word
void Cell::setPosition(size_t pos)
{
    position.push_back(pos);
}

//--------------------------------------------
//Stores the word the letter belongs to
void Cell::setWord(string word)
{
    wordItBelongs.push_back(word);
}

//--------------------------------------------
//Stores the letter
void Cell::setLetter(char l)
{
    letter = l;
}

//--------------------------------------------
//Stores the coordinates of the letter
void Cell::setXY(size_t x, size_t y)
{
    this-> x = x;
    this-> y = y;
}

//--------------------------------------------
//Sets the color of the letter
void Cell::setColor(string colour)
{
    color = colour;
}

//--------------------------------------------
//Sets all attributes
void Cell::setAllParemeters(size_t x, size_t y, size_t pos, string word, char letter, string colour, char orientation)
{
    setXY(x,y);
    setPosition(pos);
    setWord(word);
    setLetter(letter);
    setColor(colour);
    setOrientation(orientation);
}

//--------------------------------------------
//Stores orientation of word
void Cell::setOrientation(char O)
{
    orientation.push_back(O);
}

//--------------------------------------------
//Returns the line
size_t Cell::getX()
{
    return x;
}

//--------------------------------------------
//Returns the column
size_t Cell::getY()
{
    return y;
}

//--------------------------------------------
//Returns the letter
char Cell::getLetter()
{
    return letter;
}

//--------------------------------------------
//Returns position of the letter in word/words it belongs
vector<size_t> Cell::getPosition()
{
    return position;
}

//--------------------------------------------
//Return orientation(s) of the word/words
vector<char> Cell::getOrientation()
{
    return orientation;
}

//--------------------------------------------
//Returns the words the letter belongs to
vector<string> Cell::belongsTo()
{
    return wordItBelongs;
}

//--------------------------------------------
//Returns letter color
string Cell::getColor()
{
    return color;
}

