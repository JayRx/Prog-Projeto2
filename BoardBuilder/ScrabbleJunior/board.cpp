
#include <stdio.h>
#include "board.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "cell.h"
#include "colorfunctions.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

//using namespace std;

#define NO_COLOR "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define WHITE "\033[1;37m"

#define BLACK_B "\033[1;40m"
#define WHITE_B "\033[1;47m"


//Board constructor
Board::Board()
{
    lines = 10;
    cols = 10;
}

//--------------------------------------------
//Board constructor with height and width
Board::Board(const int &height, const int &width)
{
    lines = height;
    cols = width;
    vectorBoard.resize(lines);
    for (size_t i = 0; i < cols; i++)
        vectorBoard.at(i).resize(cols);
    
    for (size_t i = 1; i < lines; i++)
        for (size_t j = 1; j < cols; j++)
            vectorBoard.at(i).at(j) = Cell(i,j);
    
    for (size_t i = 1; i < lines; i++)
    {
        size_t j = 0;
        char letter = 64 + i;
        vectorBoard.at(i).at(j).setLetter(letter);
    }
    for (size_t j = 1; j < cols; j++)
       {
           size_t i = 0;
           char letter = 96 + j;
           vectorBoard.at(i).at(j).setLetter(letter);
       }
}

//--------------------------------------------
//Method to set board dimensions
void Board::setDimensions(const size_t &height, const size_t &width)
{
    lines = height;
    cols = width;
    vectorBoard.resize(lines);
    for (size_t i = 0; i < lines; i++)
        vectorBoard.at(i).resize(cols);
    
    for (size_t i = 1; i < lines; i++)
        for (size_t j = 1; j < cols; j++)
            vectorBoard.at(i).at(j) = Cell(i,j);
    
    for (size_t i = 1; i < lines; i++)
    {
        size_t j = 0;
        char letter = 64 + i;
        vectorBoard.at(i).at(j).setLetter(letter);
    }
    for (size_t j = 1; j < cols; j++)
       {
           size_t i = 0;
           char letter = 96 + j;
           vectorBoard.at(i).at(j).setLetter(letter);
       }
}


//--------------------------------------------
//Method to store a word, its orientation and its position on the board
void Board::setWordOnBoard(size_t &x, size_t &y, const char &orientation, const string &word)
{
    if (orientation == 'H')
    {
        size_t j = 0;
        for (size_t i = y; i < y + word.length(); i++)
        {
            vectorBoard.at(x).at(i).setAllParemeters(x, i, j, word, word.at(j), "BLACK", orientation);
            j++;
        }
    }
    else if (orientation == 'V')
    {
        size_t j = 0;
        for (size_t i = x; i < x + word.length(); i++)
        {
            vectorBoard.at(i).at(y).setAllParemeters(i, y, j, word, word.at(j), "BLACK", orientation);
            j++;
        }
       
    }
    else
    {
        cerr << "Provided orientation not valid \n";
        exit(1);
    }
}

//--------------------------------------------
//Set color of the tile in (x,y) to red
void Board::setTileRed(size_t x, size_t y)
{
    vectorBoard.at(x).at(y).setColor("RED");
}

//--------------------------------------------
//Builds pool from the words on the board
void Board::setPool()
{
    if (vectorBoard.empty())
    {
        cout << "Must initialize vectorBoard \n";
        exit(1);
    }
    
    for (size_t i = 1; i < lines; i++)
        for (size_t j = 1; j < cols; j++)
            if (vectorBoard.at(i).at(j).getLetter() != ' ')
                pool.push_back(vectorBoard.at(i).at(j).getLetter());
    random_shuffle(pool.begin(),pool.end());
}

//--------------------------------------------
//Returns board dimensions
vector<size_t> Board::getBoardDimensions()
{
    vector<size_t> dimensions = {lines, cols};
    return dimensions;
}

//--------------------------------------------
//Returns board
vector<vector<Cell>> Board::getBoard() const
{
    return vectorBoard;
}

//--------------------------------------------
//Returns random tile from the pool and removes it from the pool
char Board::getPoolTile()
{
    if (pool.empty())
    {
        cerr << "Must initialize pool vector \n";
        exit(1);
    }
    srand(time(NULL));
    size_t pos = 0;
    if (pool.size() != 1)
        pos = rand() % (pool.size() - 1) + 0;
    
    char tile = pool.at(pos);
    
    pool.erase(pool.begin() + pos);
    
    return tile;
}

//--------------------------------------------
//Returns tile in (x,y)
char Board::getTile(const size_t x, const size_t y)
{
    return vectorBoard.at(x).at(y).getLetter();
}

//--------------------------------------------
//Returns pool size
size_t Board::getPoolSize()
{
    return pool.size();
}

//---------------------------------------------------------------
//Returns positons of the tile in the words it belongs to
vector<size_t> Board::getTilePositionInWord(size_t &x, size_t &y)
{
    return vectorBoard.at(x).at(y).getPosition();
}

//--------------------------------------------
//Returns true if pool is empty
bool Board::isPoolEmpty()
{
    return pool.empty();
}

