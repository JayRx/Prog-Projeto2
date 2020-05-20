
#include <iostream>
#include "board.h"
#include "player.h"
#include "cell.h"
#include "colorfunctions.h"
#include "scrabbleFunctions.h"
#include <map>
#include <utility>

using namespace std;

void gameScrabble(void)
{
    Board scrabbleBoard;
    initBoard(scrabbleBoard);
    
    vector<Player> players;
    
    //Initial settings of players
    initPlayers(players);
    
    buildPool(scrabbleBoard, players.size());
    buildHand(scrabbleBoard, players);
    
    
    clrscr();
    showBoard(scrabbleBoard);
    
    /*firstTurn(players.at(0), scrabbleBoard);
    for (size_t i = 1; i < players.size(); i++)
        otherTurns(players.at(i), scrabbleBoard);
    
    do
    {
        for (size_t i = 0; i < players.size(); i++)
            otherTurns(players.at(i), scrabbleBoard);
    } while (!allHandsEmpty(players));*/
    
   int count = 0;
   map<string, char> possibleMoves = search(players.at(0), scrabbleBoard, 1);
   
   if (!possibleMoves.empty())
   {   firstMoveA(players.at(0), scrabbleBoard, possibleMoves);
       count++;
       possibleMoves = search(players.at(0), scrabbleBoard, 2);
       if (!possibleMoves.empty())
       { firstMoveB(players.at(0), scrabbleBoard, possibleMoves); count++;}
       
       //else
         //  exchangeTiles(player, board);
       
       while(count)
       {   addPoolTile(players.at(0), scrabbleBoard);
           count--;
       }
   }

    for (size_t i = 1; i < players.size(); i++)
       {
           int count = 0;
           map<string, char> possibleMoves = search(players.at(i), scrabbleBoard, 2);
           if (!possibleMoves.empty())
               {   Word palavra = move(players.at(i), scrabbleBoard, possibleMoves);
                   possibleMoves = search(players.at(i), scrabbleBoard, 3, palavra.words, palavra.x, palavra.y);
                   count++;
                   if (!possibleMoves.empty())
                   {   anotherMove(players.at(i), scrabbleBoard, palavra, possibleMoves); count++;}
                   else
                       //exchangeTiles(players, board);
                       cout << "No more \n";
               }
           while(count)
           {
               addPoolTile(players.at(i), scrabbleBoard);
               count--;
           }
       }
    
    for (size_t i = 0; i < players.size(); i++)
    {
        int count = 0;
        map<string, char> possibleMoves = search(players.at(i), scrabbleBoard, 2);
        if (!possibleMoves.empty())
            {   Word palavra = move(players.at(i), scrabbleBoard, possibleMoves);
                possibleMoves = search(players.at(i), scrabbleBoard, 3, palavra.words, palavra.x, palavra.y);
                count++;
                if (!possibleMoves.empty())
                {   anotherMove(players.at(i), scrabbleBoard, palavra, possibleMoves); count++;}
                else
                    //exchangeTiles(players, board);
                    cout << "No more \n";
            }
        while(count)
        {
            addPoolTile(players.at(i), scrabbleBoard);
            count--;
        }
    }
    
    whoWins(players);
        
}


int main() {
   
    gameScrabble();
    
    return 0;
}
