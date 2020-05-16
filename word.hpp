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
    int size;
    string value;
    char position[2];
    char orientation;
};
