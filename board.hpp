#include <iostream>
#include <vector>

#include "word.hpp"

using namespace std;

class Board {
  public:
    Board(); // Default Constructor
    Board(int width, int height); // Parameterized Constructor
    ~Board(); // Destructor
    void setWidth(int width); // Witdh Setter
    void setHeight(int height); // Height Setter
    int getWidth() const; // Width Getter
    int getHeight() const; // Height Getter
    char** getTable() const; // Table Getter
    vector<Word> * getWords(); // Words Getter
    void printTable(); // Print Current Table Status
    bool placeWord(string word, int *pos, char orientation); // Adds word to word vector and changes table
    void addWord(string word, int *pos, char orientation);

  private:
    int width;
    int height;
    vector<Word> words;
    char ** table;
};
