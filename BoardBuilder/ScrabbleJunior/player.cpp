
#include <stdio.h>
#include "player.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "colorfunctions.h"

#define NO_COLOR "\033[0m"
#define BLACK "\033[0;30m"
#define WHITE "\033[1;37m"

//Background color codes
#define BLACK_B "\033[1;40m"
#define WHITE_B "\033[1;47m"


IdNum Player::numPlayers = 0;

//Object construction
//Increases the numPlayers variables, assigns a number to the player's id and a name. The score is set to 0
Player::Player(const string &name)
{
    numPlayers++;
    id = numPlayers;
    score = 0;
    playerName = name;
}

//Sets player's name
void Player::setName(const string &name)
{
    playerName = name;
}

//Sets player's score
void Player::setScore(int score)
{
    this->score = score;
}

//Returns player's id
unsigned long Player::getId()
{
    return id;
}

//Returns player's score
int Player::getScore()
{
    return score;
}

//Returns player's name
string Player::getName()
{
    return playerName;
}

vector<char> Player::getHand()
{
    return playerHand;
}

//Adds a tile to the player's hand
void Player::addTile(char tile)
{
    playerHand.push_back(tile);
}

//Removes the chosen tile from the hand
//If the chosen tile doesn't match any tile of the hand, the function returns false
bool Player::removeTile(char tile)
{
    bool removed = true;
    
    //Searches the position of the chosen tile
    vector<char>::iterator it = find(playerHand.begin(), playerHand.end(), tile);
    
    //If the tile is not in hand, returns a error message and the tile won't be removed. Thus, removed is false
    if (it == playerHand.end())
    {
        cout << "Chosen tile does not belong to player's hand \n";
        removed = false;
    }
    //If the tile is in hand, it is successfully removed from the hand and variable removed is true
    else
    {
        size_t index = distance(playerHand.begin(), it);
    
        //Erases the tile in the position returned by distance
        playerHand.erase(playerHand.begin() + index);
    }
    
    return removed;
}

//Checks if the chosen tile is in player's hand
bool Player::isTileOnHand(char tile)
{
    vector<char>::iterator it = find(playerHand.begin(), playerHand.end(), tile);
   
    if (it != playerHand.end())
        return true;
    else
        return false;
}

//Checks if the hand is empty
bool Player::isHandEmpty()
{
    return playerHand.empty();
}

//Shows the player's hand
void Player::showTiles()
{
    cout << " ";
    for (int i = 0; i < (3 * playerHand.size() + playerHand.size() - 1); i++)
        cout << "-";
    cout << endl;
    cout << "| ";
    for (size_t i = 0; i < playerHand.size(); i++)
        cout << playerHand.at(i) << " | ";
    cout << endl;
    cout << " ";
    for (int i = 0; i < (3 * playerHand.size() + playerHand.size() - 1); i++)
        cout << "-";
    cout << endl;
    
}
