
#ifndef cell_h
#define cell_h

#include <string>
#include <vector>

using namespace std;



class Cell
{
public:
    Cell();
    Cell(const size_t line, const size_t col);
    void setPosition(size_t pos);
    void setWord(string word);
    void setLetter(char l);
    void setXY(size_t x, size_t y);
    void setColor(string colour);
    void setOrientation(char O);
    size_t getX();
    size_t getY();
    vector<size_t> getPosition();
    char getLetter();
    vector<char> getOrientation();
    vector<string> belongsTo();
    string getColor();
    void setAllParemeters( size_t x,  size_t y, size_t pos, string word, char letter, string colour, char orientation);
private:
    size_t x, y;
    char letter;
    vector<size_t> position;
    vector<string> wordItBelongs;
    vector<char> orientation;
    string color;
};

#endif /* cell_h */
