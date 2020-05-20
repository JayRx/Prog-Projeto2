
#ifndef PLAYER_h
#define PLAYER_h

#include<iostream>
#include<vector>

using namespace std;

typedef unsigned long IdNum;

class Player{
public:
    Player(const string &name);
    void setName(const string &name);
    void setScore(int score);
    IdNum getId();
    int getScore();
    string getName();
    vector<char> getHand();
    void addTile(char tile);
    bool removeTile(char tile);
    bool isTileOnHand(char tile);
    bool isHandEmpty();
    void showTiles();
private:
    static IdNum numPlayers;
    IdNum id;
    string playerName;
    int score;
    vector<char> playerHand;
};

#endif /* player_h */
