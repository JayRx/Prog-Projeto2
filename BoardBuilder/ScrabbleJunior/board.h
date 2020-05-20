#ifndef BOARD_h
#define BOARD_h


#include <vector>
#include <string>
#include "cell.h"

using namespace std;

class Board{
public:
    Board();
    Board(const int &height, const int &width);
    void setDimensions(const size_t &height, const size_t &width);
    void setWordOnBoard(size_t &x, size_t &y, const char &orientation, const string &word);
    void setPool();
    void setTileRed(size_t x, size_t y);
    vector<size_t> getBoardDimensions();
    vector<vector<Cell>> getBoard() const;
    char getTile(const size_t x, const size_t y);
    char getPoolTile();
    size_t getPoolSize();
    vector<size_t> getTilePositionInWord(size_t &x, size_t &y);
    bool isPoolEmpty(void);
private:
    size_t lines, cols;
    vector<vector<Cell>> vectorBoard;
    vector<char> pool;
};

#endif /* board_h */

