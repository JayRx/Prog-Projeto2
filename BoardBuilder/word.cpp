#include <iostream>
#include "word.hpp"

using namespace std;

// Constructors

// Default Constructor
Word::Word() {

}

// Parameterized Constructor
Word::Word(string value, char* position, char orientation) {
  this->value = value;
  this->position[0] = position[0];
  this->position[1] = position[1];
  this->orientation = orientation;
  this->size = value.length();
}

// Setters

// Sets the Word's String
void Word::setValue(string value) {
  this->value = value;
  this->size = value.length();
}

// Sets the Word's Position
void Word::setPositon(char position[2]) {
  this->position[0] = position[0];
  this->position[1] = position[1];
}

// Sets the Word's Orientation
void Word::setOrientation(char orientation) {
  this->orientation = orientation;
}

// Getters

// Gets the number of characters of Word's string
int Word::getSize() const {
  return this->size;
}

// Gets the string of a Word
string Word::getValue() const {
  return this->value;
}

// Gets the position of a Word
char* Word::getPosition() {
  return this->position;
}

// Gets the orientation of a Word
char Word::getOrientation() const {
  return this->orientation;
}
