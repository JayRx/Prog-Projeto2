#include <iostream>
#include "word.hpp"

using namespace std;

// Constructors
Word::Word() {

}

Word::Word(string value, char* position, char orientation) {
  this->value = value;
  this->position[0] = position[0];
  this->position[1] = position[1];
  this->orientation = orientation;
  this->size = value.length();
}

// Setters
void Word::setValue(string value) {
  this->value = value;
  this->size = value.length();
}

void Word::setPositon(char position[2]) {
  this->position[0] = position[0];
  this->position[1] = position[1];
}

void Word::setOrientation(char orientation) {
  this->orientation = orientation;
}

// Getters
int Word::getSize() const {
  return this->size;
}

string Word::getValue() const {
  return this->value;
}

char* Word::getPosition() {
  return this->position;
}

char Word::getOrientation() const {
  return this->orientation;
}
