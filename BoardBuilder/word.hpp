#include <iostream>
using namespace std;

class Word {
  public:
    Word(); // Default Constructor
    Word(string value, char* position, char orientation); // Parameterized Constructor
    void setValue(string value); // Value Setter
    void setPositon(char* position); // Position Setter
    void setOrientation(char orientation); // Orientation Setter
    int getSize() const; // Size Getter
    string getValue() const; // Value Getter
    char* getPosition(); // Position Getter
    char getOrientation() const; // Orientation Getter

  private:
    int size; // Number of characters of Word's string
    string value; // Word's String
    char position[2]; // Word's Position (Ex: Aa)
    char orientation; // Word's Orientation ('H' or 'V')
};
