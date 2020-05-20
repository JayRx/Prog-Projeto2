
#ifndef scrabbleFunctions_h
#define scrabbleFunctions_h

#include <iostream>
#include <fstream>
#include <map>
#include "cell.h"
#include "board.h"
#include "player.h"
#include "colorfunctions.h"

struct Word {
    size_t x, y;
    vector<string> words;
    char tile;
};

//Initialize the board
void initBoard(Board &scrabbleBoard);

//Displays the board
void showBoard(Board &board);

//Initialize the players
void initPlayers(vector<Player> &players);

//Build pool
void buildPool(Board &board, size_t numPlayers);

//Build a hand for each player
void buildHand(Board &board, vector<Player> &players);

//Add a pool tile to the player's hand
void addPoolTile(Player &player, Board &board);

//Checks if all hands are empty
bool allHandsEmpty(vector<Player> player);

//Shows hand of tiles to the player.
//Returns the tile chosen by the player
char getHandTile(Player &player);

//Checks if chosen line is within the range of the board
bool isLineValid(char x, Board &board);

//Checks if chosen column is within the range of the board
bool isColValid(char y, Board &board);

//Asks to user where he/she wants to place the tile
string getCoordinates(Board &board);

//Checks if the tile chosen from the hand corresponds to the chosen position on the board
bool matchingTiles(char tile, Board &board, size_t x, size_t y);

//Checks if the tile in the chosen coordinates is a tile that is already filled
bool forbiddenTile(char tile, Board &board, size_t x, size_t y);

//Checks if tile in the chosen coordinates corresponds to a first letter
bool firstLetter(size_t x, size_t y, Board &board);

//Checks if the tiles previous to the one in coordinates (x,y) are filled
bool isPreviousTileFilled(size_t x, size_t y, Board &board);

//Checks if any of the tiles previous to the one in coordinates (x,y) was filled by the player on the previous move
bool filledByPlayer(size_t x1, size_t y1, size_t x2, size_t y2, vector<string> words, Board &board);

//Function for the first turn 
void firstTurn(Player &player, Board &board);

//Function for the first turn in order to place the first tile
void firstMoveFT(Player &player, Board &board, map<string, char> listTiles);

//Function for the first turn in order to place the second tile
void secondMoveFT(Player &player, Board &board, map<string, char> listTiles);

//Function for other turns
void otherTurns(Player &player, Board &board);

//Function for the first move of other turns
Word firstMoveOT(Player &player, Board &board, map<string, char> listTiles);

//Function for the second move of other turns
void secondMoveOT(Player &player, Board &board, Word palavra, map<string, char> listTiles);

//Searches for all possibles moves, based on current state of the board and on player's hand
map<string, char> search(Player &player, Board &board, int no_move, vector<string> words = {"XXXX", "XXXX"},  size_t x2 = 0, size_t y2 = 0);

//Exchange two tiles of player's hand for two tiles from pool
void exchangeTiles(Player &player, Board &board);

//Updates player's score
void calculateScore(size_t x, size_t y, Board &board, Player &player);

//Determines the winner of the game
void whoWins(vector<Player> players);
#endif /* scrabbleFunctions_h */
