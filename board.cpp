#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.hpp"

using namespace std;

string int_to_string(int n) {
	ostringstream outstr;
	outstr << n;
	return outstr.str();
}

void setcolor(unsigned int color) {
	cout << "\033[0;"+int_to_string(color)+"m";
	cout.flush();
}

// Constructors

// Default Constructor
Board::Board() {
}

// Parameterized Constructor
Board::Board(int width, int height) {
  char ** s_array;

  this->width = width;
  this->height = height;

  this->table = (char **) malloc(height * sizeof(char*));
  for(int i = 0; i < height; i++) {
    this->table[i] = (char *) malloc((width + 1) * sizeof(char));
    for(int j = 0; j < width; j++) {
      this->table[i][j] = '-';
    }
    this->table[i][width] = '\0';
  }

  cout << "-> Created Board " << width << "x" << height << "!" << endl;
}

// Destructor
Board::~Board() {
  /*for(int i = 0; i < this->height; i++) {
    free(this->table[i]);
  }
  free(this->table);*/
}

// Setters

// Sets the Board's Width
void Board::setWidth(int width) {
  this->width = width;
}

// Sets the Board's Height
void Board::setHeight(int height) {
  this->height = height;
}

//Getters

// Gets the Board's Width
int Board::getWidth() const {
  return this->width;
}

// Gets the Board's Height
int Board::getHeight() const {
  return this->height;
}

// Gets the Board's Table
char** Board::getTable() const {
  return this->table;
}

// Gets the Board's Word Vector
vector<Word> * Board::getWords() {
  return &words;
}

// Prints Board's Table
void Board::printTable() {
  char aux;
  cout << endl << " ";

  setcolor(36);
  for(int i = 0; i < this->width; i++) {
    aux = (char) (97 + i);
    cout << aux;
  }

  cout << endl;

  for(int i = 0; i < this->height; i++) {
    setcolor(36);
    aux = (char) (65 + i);
    cout << aux;
    setcolor(37);
    cout << this->table[i];
    cout << endl;
  }

  cout << endl;
}

// Other Functions

// Adds Word to Board's Word Vector
void Board::addWord(string value, int *position, char orientation) {
  char *pos;

  pos = (char *) malloc(2 * sizeof(char));

  pos[0] = (char) (position[0] + 65);
  pos[1] = (char) (position[1] + 97);

  Word newWord(value, pos, orientation);

  this->words.push_back(newWord);
}

// Checks if it is possible to place a Word in the Board's Table and calls Board::addWord
bool Board::placeWord(string word, int *pos, char orientation) {
  char aux;
  Word newWord;

  if(orientation == 'H') {
    if(pos[1] + word.length() > this->width)
      return false;

    for(int i = 0; i < word.length(); i++) {
      aux = this->table[pos[0]][pos[1] + i];
      if(aux != '-' && aux != word.at(i))
        return false;
    }

    for(int i = 0; i < word.length(); i++) {
      this->table[pos[0]][pos[1] + i] = word.at(i);
    }

  } else if(orientation == 'V') {
    if(pos[0] + word.length() > this->height)
      return false;

    for(int i = 0; i < word.length(); i++) {
      aux = this->table[pos[0] + i][pos[1]];
      if(aux != '-' && aux != word.at(i))
        return false;
    }

    for(int i = 0; i < word.length(); i++) {
      this->table[pos[0] + i][pos[1]] = word.at(i);
    }

  } else {
    return false;
  }

  addWord(word, pos, orientation);

  return true;
}
