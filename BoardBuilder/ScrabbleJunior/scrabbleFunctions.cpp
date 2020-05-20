
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "scrabbleFunctions.h"
#include "cell.h"
#include "board.h"
#include "player.h"
#include "colorfunctions.h"
#include <map>
#include <utility>

//Text color codes
#define NO_COLOR "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define WHITE "\033[1;37m"

//Background color codes
#define BLACK_B "\033[1;40m"
#define WHITE_B "\033[1;47m"

using namespace std;

//------------------------------------------
//Initializes board
void initBoard(Board &scrabbleBoard)
{
    clrscr();
    
    string boardFilename;
    
    cout << "Input the game filename  \n";
    cin >> boardFilename;
    cout << endl;
    
    //File stream for board file
    ifstream boardStr;
    
    //Opens file
    boardStr.open(boardFilename);
    //Checks if opening file has succeeded
    if(boardStr.fail())
    {
        cerr << boardFilename << " opening failed \n"; //Returns error message in case of failure and exits
        exit(1);
    }
    
    int height, width;
    string coordinates, word, inform;
    char orientation, x, y, cross;
    
    //Extraction of the board's dimensions
    boardStr >> height >> cross >> width;
    
    //Set dimensions of the board
    //It is sumed 1 to the number of lines (height) to add a line on board's top which will contain labels for the columns
    //It is sumed 1 to the number of columns (width) to add a column on the left side of board which will contain labels for the lines
    scrabbleBoard.setDimensions(height+1, width+1);
    
    while(!boardStr.eof() && boardStr.peek() != 0)
    {
        //Extraction of: coordinates of the word on the board; word's orientation; and word itself
        boardStr >> coordinates >> orientation >> word;
    
        x = coordinates.at(0);
        
        //Checks for a board representation
        //If a board representation exists, the previous extraction is not suitable for it nor this function as it builds its own board
        if (x > 96)
            break;

        y = coordinates.at(1);
        
        //Conversion of char coordinates x and y to size_t coordinates a and b
        //X corresponds to the lines, which are represented by uppercase letters. Line 1 is represented by A, line 2 by B, and so on
        //Y corresponds to the colums, which are reprsented by lowercase letters. Column 1 is represented by a, line 2 is represented by b, and so on
        //Thus, 64 must be subtracted to x and 96 must be sutracted to y,
        //so that its values match the number of the line and the number of the column, respectively
        size_t a,b;
        a = x - 64;
        b = y - 96;
        
        //Sets the word received on the board, according to the given orientation and the coordinates of the word's first letter
        scrabbleBoard.setWordOnBoard(a,b, orientation, word);
        
    }
    
    boardStr.close();
}

//------------------------------------------
//Shows the board
void showBoard(Board &board)
{
    
    gotoxy(7,3);
    cout << WHITE << BLACK_B;
    
    //Displays the top border of the board with a white text color in a black background for the columns
    gotoxy(10,3);
    for (size_t i = 1; i < board.getBoardDimensions().at(1); i++)
        cout << board.getBoard().at(0).at(i).getLetter() << ' ';
    cout << BLACK_B << NO_COLOR << endl;
    
    //Displays the lines with a white text color in a black background
    for (size_t i = 1; i < board.getBoardDimensions().at(0); i++)
    {
        gotoxy(7, i + 3);
        cout << WHITE << BLACK_B << ' ' << board.getBoard().at(i).at(0).getLetter() << ' ' << NO_COLOR;
    }
    
    //Displays the board
    for (size_t i = 1; i < board.getBoardDimensions().at(0); i++)
    {
        gotoxy(10,i + 3);
        cout << BLACK << WHITE_B;
        for (size_t j = 1; j < board.getBoardDimensions().at(1); j ++)
        {
            if (board.getBoard().at(i).at(j).getColor() == "RED" )  //If a tile has been filled by a player, the color of the tile will be red
                cout << RED << WHITE_B;
            else
                cout << BLACK << WHITE_B;
            cout << board.getBoard().at(i).at(j).getLetter() << ' ';
            
            
        }
        cout << NO_COLOR << endl;
    }
    
    gotoxy(7, 3 + board.getBoardDimensions().at(0));
    const int PRECISION = 3 + 2*(board.getBoardDimensions().at(1)-1);
    cout << BLACK_B << setw(PRECISION) << ' ';
    gotoxy(PRECISION + 1, board.getBoardDimensions().at(0) + 3);
    cout << NO_COLOR;
    cout << endl;
}

//------------------------------------------
//Initialize the players
void initPlayers(vector<Player> &players)
{
    int numPlayers;
    cout << "How many players? (2-4 players) ";
    cin  >> numPlayers;
    cout << endl;
    cin.ignore(1000, '\n');
    
    //Checks if the number of players is within the valid range
    //Otherwise, returns an error message and exits the game
    if (numPlayers < 2 || numPlayers > 4)
    {
        cerr << "Number of players invalid. \n";
        exit(1);
    }
    
    string name;
    for (size_t i = 0; i < numPlayers; i++)
    {
        cout << "Player " << i + 1 << ", what is your name? ";
        getline(cin, name);
        players.push_back(Player(name));
    }
}

//------------------------------------------
//Builds pool
void buildPool(Board &board, size_t numPlayers)
{
    //Builds pool of tiles
    board.setPool();
    
    //Checks if there is enough tiles for all players, according to the chosen board and the number of players
    if (board.getPoolSize()/numPlayers < 7)
    {
        cout << "The board does not have enough tiles for all players. \n";
        cout << "Reduce the number of players or change the board. \n";
        exit(1);
    }
}

//------------------------------------------
//Builds hands for all players
void buildHand(Board &board, vector<Player> &players)
{
    //For each player, build his/her hand of tiles formed by 7 tiles
    //On the second for cycle, for each iteration, a random tile is removed from the pool and added to the player's hand
    for (size_t i = 0; i < players.size(); i++)
        for (int j = 1; j < 8; j++)
            players.at(i).addTile(board.getPoolTile());
}

//------------------------------------------
//Removes a tile from the pool and adds it to the player's hand
void addPoolTile(Player &player, Board &board)
{
    if (!board.isPoolEmpty())
        player.addTile(board.getPoolTile());
    //else
        //cout << "The pool is empty \n";
}

//------------------------------------------
//Checks if all hands are empty
bool allHandsEmpty(vector<Player> player)
{
    bool empty = true;
    for (size_t i = 0; i < player.size(); i++)
        if (!player.at(i).isHandEmpty())
            empty = false;
    return empty;
}

//------------------------------------------
//Shows hand of tiles to the player.
//Returns the tile chosen by the player
char getHandTile(Player &player)
{
    char handTile;
    cout << endl;
    player.showTiles();
    cout << "Choose a tile: ";
    cin >> handTile;
    cin.ignore(1000, '\n');
  
    return toupper(handTile);
}

//------------------------------------------------------
//Checks if chosen line is within the range of the board
bool isLineValid(char x, Board &board)
{
    if (x < 65 || x > (board.getBoardDimensions().at(0) + 64))
    {
        cout << "Chosen line not valid. \n";
        return false;
    }
    else
        return true;
}

//--------------------------------------------------------
//Checks if chosen column is within the range of the board
bool isColValid(char y, Board &board)
{
    if (y < 97 || y > (board.getBoardDimensions().at(1) + 96))
    {
        cout << "Chosen column not valid. \n";
        return false;
    }
    else
        return true;
}

//---------------------------------------------------------------------------------
//Asks the user the line and the column where he/she wants to place the chosen tile
//Returns chosen coordinates
string getCoordinates(Board &board)
{
    string coordinates;
    
    cout << "Where do you want to place it? \n";
    cout << "Indicate line in uppercase and column in lowercase (example: Ab) ";
    cin >> coordinates;
    return coordinates;
}

//--------------------------------------------------------------------------------------
//Checks if the tile chosen from the hand corresponds to the tile on the chosen position
bool matchingTiles(char tile, Board &board, size_t x, size_t y)
{
    if (tile != board.getTile(x, y))
        return false;
    else
        return true;
}

//----------------------------------------------------------------
//Checks if the tile on the chosen position has already been chosen
bool forbiddenTile(char tile, Board &board, size_t x, size_t y)
{
    if (board.getBoard().at(x).at(y).getColor() == "RED")
        return true;
    else
        return false;
}

//---------------------------------------------------------------------------------
//Checks if the tile on the chosen position corresponds to a first letter on a word
bool firstLetter(size_t x, size_t y, Board &board)
{
    vector<size_t> positions = board.getTilePositionInWord(x, y);
    for (size_t i = 0; i < positions.size(); i++)
        if (positions.at(i) == 0)
            return true;
    return false;
}

//---------------------------------------------------------------------------------
//Checks if the tiles previous to the one in coordinates (x,y) are filled
bool isPreviousTileFilled(size_t x, size_t y, Board &board)
{
    bool value = true;
    vector<size_t> positions = board.getBoard().at(x).at(y).getPosition();
    vector<char> orientations = board.getBoard().at(x).at(y).getOrientation();
    
    //Tile in (x,y) belongs to 2 words
    if (positions.size() == 2)
    {
        vector<bool> values = {true, true};
        for (size_t i = 0; i < 2; i++)
        {
            //If the tile in (x,y) corresponds to a first letter in any of the words it belongs,
            //there is no need to check previous tiles. The move is valid.
            if (firstLetter(x, y, board))
                break;
            
            if (orientations.at(i) == 'H')
            { for (size_t j = positions.at(i); j > 0; j--)
                {   if (board.getBoard().at(x).at(y-j).getColor() == "BLACK")
                    {
                        values.at(0) = false;
                        break;
                    }
                }
            }
            else if (orientations.at(i) == 'V')
            {   for (size_t j = positions.at(i); j > 0; j--)
                {if (board.getBoard().at(x-j).at(y).getColor() == "BLACK")
                        {
                            values.at(1) = false;
                            break;
                        }
                }
            }
        }
        
        //The function checks the previous tiles on both words.
        //The move is only non valid when in both words there are previous tiles to be filled
        if (values.at(0) == false && values.at(1) == false)
            value = false;
    }
    
    //Tile in (x,y) belongs to just 1 word. The function checks the tiles previous to the one in coordinates (x,y)
    //When it enconters a black tile (not filled), it returns false
    else if (positions.size() == 1)
    {
        switch(orientations.at(0))
        {
            case 'H':
                {for (size_t j = positions.at(0); j > 0; j--)
                    if (board.getBoard().at(x).at(y-j).getColor() == "BLACK")
                        value = false; break;
                }
                break;
            case 'V':
                { for (size_t j = positions.at(0); j > 0; j--)
                    if (board.getBoard().at(x-j).at(y).getColor() == "BLACK")
                        value = false; break;
                }
                break;
        }
    }
    return value;
}


//----------------------------------------------------------------------------------------------
//A player must play to tiles on his/her turn
//(x1,y1) are the chosen coordinates of the previous move
//(x2,y2) are the chosen coordinates of the current move
//If both tiles belong to the same word, the function returns true
bool filledByPlayer(size_t x1, size_t y1, size_t x2, size_t y2, vector<string> words, Board &board)
{
    vector<string> words2 = board.getBoard().at(x2).at(y2).belongsTo();
    for (size_t i = 0; i < words.size(); i++)
        for (size_t j = 0; j < words2.size(); j++)
            if (words.at(i) == words2.at(j))
            {
                return true;
                break;
            }
    return false;
}



//-----------------------------------------------------------------------------------------------------------
//Searches for all possibles moves, based on current state of the board and on player's hand
map<string,char> search(Player &player, Board &board, int no_move, vector<string> words, size_t x2, size_t y2)
{
    map<string, char> listWords;
    string coordinates;
   // char* letters;
   
    for (auto x : player.getHand())
        for (size_t i = 1; i < board.getBoardDimensions().at(0); i++)
            for (size_t j = 1; j < board.getBoardDimensions().at(1); j++)
                switch (no_move)
                { case 1:
                        if (matchingTiles(x, board, i, j) && firstLetter(i, j, board))
                            {
                                //coordinates = letters[i] + tolower(letters[j]);
                                coordinates = to_string(i) + ' ' + to_string(j);
                                listWords.insert(pair<string, char >(coordinates, board.getTile(i,j)));
                            }
                break;
                case 2:
                        if (matchingTiles(x, board, i, j) && !forbiddenTile(x, board, i, j) && (firstLetter(i, j, board) || isPreviousTileFilled(i, j, board)))
                            {
                                coordinates = to_string(i) + ' ' + to_string(j);
                                
                                listWords.insert(pair<string, char >(coordinates, board.getTile(i,j)));
                            }
                        break;
                case 3:
                    if (matchingTiles(x, board, i, j) && !forbiddenTile(x, board, i, j) && !filledByPlayer(x2, y2, i, j, words, board) && (firstLetter(i, j, board) || isPreviousTileFilled(i, j, board)))
                        {
                            coordinates = to_string(i) + ' ' + to_string(j);
                            listWords.insert(pair<string, char > (coordinates, board.getTile(i,j)));
                        }
                        break;
                }
    return listWords;
}

//---------------------------------------------------------------------------------
//Exchange two tiles of player's hand for two tiles from pool
void exchangeTiles(Player &player, Board &board)
{
   if (!board.isPoolEmpty())
   {
       string chosenTiles;
       cout << "You have no valid moves. \n";
       cout << "Chose two of your tiles to exchange for two of the pool. \n";
       player.showTiles();
       cout << "Chose the first tile: \n";
       //getline(cin, chosenTiles);
   }
   else
    cout << player.getName() <<  "there are no more valid moves \n";
}

//---------------------------------------------------------------------------------
//First move of the first turn 
void firstMoveA(Player &player, Board &board, map<string, char> listTiles)
{
    cout << endl;
    cout << player.getName() << " it's your turn to play \n";
    char handTile; string coordinates;
    size_t a, b;
    
    if (!listTiles.empty())
    {   cout << "Possible moves \n";
        for (auto x : listTiles)
            cout << x.first << ' ' << x.second << endl;
    }
    
    do
    {
        //Aks the player to choose a tile while chosen tile does not the player's hand
        do { handTile = getHandTile(player); } while (!player.removeTile(handTile));
        do
        { coordinates = getCoordinates(board);
            if (coordinates.size() == 1)
                coordinates = coordinates + ' ';
        } while (!isLineValid(coordinates.at(0), board) || !isColValid(coordinates.at(1), board));
        
        //Conversion of char coordinates x and y to size_t coordinates a and b
        //X corresponds to the lines, which are represented by uppercase letters. Line 1 is represented by A, line 2 by B, and so on
        //Y corresponds to the colums, which are reprsented by lowercase letters. Column 1 is represented by a, line 2 is represented by b, and so on
        //Thus, 64 must be subtracted to x and 96 must be sutracted to y,
        //so that its values match the number of the line and the number of the column, respectively
        a = coordinates.at(0)-64;
        b = coordinates.at(1) -96;
        if (!matchingTiles(handTile, board, a, b))
            {
                cout << "Chosen tile and chosen letter on the board do not match. \n";
                player.addTile(handTile);
            }
        
        else if (!firstLetter(a, b, board))
            {
                cout << "Must choose a first letter \n";
                player.addTile(handTile);
            }
        
    }while(!matchingTiles(handTile, board, a, b) || !firstLetter(a, b, board));
    
    //Set color attribute to red
    board.setTileRed(a, b);
        
    clrscr();
    showBoard(board);
    
}

//---------------------------------------------------------------------------------
//Second move of the first turn
void firstMoveB(Player &player, Board &board, map<string, char> listTiles)
{
    cout << endl;
    cout << player.getName() << " it's your turn to play \n";
    char handTile; string coordinates;
    size_t a, b;
    
    if (!listTiles.empty())
    {cout << "Possible moves \n";
        for (auto x : listTiles)
            cout << x.first << ' ' << x.second << endl;
    }
    
    //Similar to firstMoveA
    do {
        //Checks if the chosen tile belongs to player's hand and if chosen coordinates are valid
        do { handTile = getHandTile(player);} while (!player.removeTile(handTile));
        do
        { coordinates = getCoordinates(board);
            if (coordinates.size() == 1)
                coordinates = coordinates + ' ';
        } while (!isLineValid(coordinates.at(0), board) || !isColValid(coordinates.at(1), board));
        
        a = coordinates.at(0)-64;
        b = coordinates.at(1) -96;
        
        //Checks if there is a match between the chosen tile and the tile on the chosen coordinates
        if (!matchingTiles(handTile, board, a, b))
        {
            cout << "Chosen tile and chosen letter on the board do not match. \n";
            player.addTile(handTile);
        }
        //Checks if tile on the board has not been filled
        else if (forbiddenTile(handTile, board, a, b))
        {
            cout << "Chosen letter already taken \n";
            player.addTile(handTile);
        }
        //Checks if the tile on the board is a first letter
        //And if the tiles previous to the one in coordinates (a, b) are filled
        else if (!firstLetter(a, b, board) && !isPreviousTileFilled(a, b, board))
        {
            cout << "Must choose a first or previous letter \n";
            player.addTile(handTile);
        }
        
    } while(!matchingTiles(handTile, board, a, b) || forbiddenTile(handTile, board, a, b) || (!firstLetter(a, b, board) && !isPreviousTileFilled(a, b, board)));
    
    //Set color attribute to red
    board.setTileRed(a, b);
    
    //Calculates player's score after the move
    calculateScore(a, b, board, player);
    
    clrscr();
    showBoard(board);
    
}

//---------------------------------------------------------------------------------
//First turn
void firstTurn(Player &player, Board &board)
{
    int count = 0;
    map<string, char> possibleMoves = search(player, board, 1);
    
    if (!possibleMoves.empty())
    {   firstMoveA(player, board, possibleMoves);
        count++;
        possibleMoves = search(player, board, 2);
        if (!possibleMoves.empty())
        { firstMoveB(player, board, possibleMoves); count++;}
        
        //else
          //  exchangeTiles(player, board);
        
        while(count)
        {   addPoolTile(player, board);
            count--;
        }
    }
}


//---------------------------------------------------------------------------------
//First move of other turns
//Returns a variable of type Word which will be import for the second move
Word move(Player &player, Board &board, map<string, char> listTiles)
{
    cout << endl;
    cout << player.getName() << " it's your turn to play \n";
    char handTile; string coordinates;
    size_t a, b;
    
    if (!listTiles.empty())
        for (auto x : listTiles)
            cout << x.first << ' ' << x.second << endl;
    
    do {
        //Checks if the chosen tile belongs to player's hand and if chosen coordinates are valid
        do {handTile = getHandTile(player);} while (!player.removeTile(handTile));
        do
        { coordinates = getCoordinates(board);
            if (coordinates.size() == 1)
                coordinates = coordinates + ' ';
        }while (!isLineValid(coordinates.at(0), board) || !isColValid(coordinates.at(1), board));
        
        a = coordinates.at(0)-64;
        b = coordinates.at(1) -96;
        
        //Checks if there is a match between the chosen tile and the tile on the chosen coordinates
        if (!matchingTiles(handTile, board, a, b))
        {
            cout << "Chosen tile and chosen letter on the board do not match. \n";
            player.addTile(handTile);
        }
        //Checks if tile on the board has not been filled
        else if (forbiddenTile(handTile, board, a, b))
        {
            player.addTile(handTile);
            cout << "Tile already taken \n";
        }
        //Checks if the tile on the board is a first letter
        //And if the tiles previous to the one in coordinates (a, b) are filled
        else if (!isPreviousTileFilled(a, b, board) && !firstLetter(a, b, board))
        {
            player.addTile(handTile);
            cout << "Must choose a previous letter \n";
        }
    }
    while(!matchingTiles(handTile, board, a, b) || forbiddenTile(handTile, board, a, b) || ((!isPreviousTileFilled(a, b, board)) && (!firstLetter(a, b, board))));
    
   
    //Set color attribute to red
    board.setTileRed(a, b);

    //Calculates player's score after the move
    calculateScore(a, b, board, player);
    
    //worplayed contains the chosen coordinates on this move and the word (or words) which the tile is part of
    //wordplayed is important for the second move in the second turns onwards
    Word wordPlayed;
    wordPlayed.x = coordinates.at(0)-64;
    wordPlayed.y = coordinates.at(1)-96;
    wordPlayed.words = board.getBoard().at(a).at(b).belongsTo();
    
    clrscr();
    showBoard(board);
    
    return wordPlayed;
}

//---------------------------------------------------------------------------------
//Second move of other turns
void anotherMove(Player &player, Board &board, Word wordPlayed, map<string, char> listTiles)
{
    cout << endl;
    cout << player.getName() << " it's your turn to play \n";
    char handTile; string coordinates;
    size_t a, b;
    bool filled;
    
   //map<string, char> listWords = search(player, board, 3, wordPlayed.words, wordPlayed.x, wordPlayed.y);
    if (!listTiles.empty())
        for (auto x : listTiles)
            cout << x.first << ' ' << x.second << endl;
    
    do {
        //Checks if the chosen tile belongs to player's hand and if chosen coordinates are valid
        do {handTile = getHandTile(player);} while (!player.removeTile(handTile));
        do
        { coordinates = getCoordinates(board);
            if (coordinates.size() == 1)
                coordinates = coordinates + ' ';
         }while (!isLineValid(coordinates.at(0), board) || !isColValid(coordinates.at(1), board));
        
        a = coordinates.at(0)- 64;
        b = coordinates.at(1) - 96;
         
        //Checks if any of the previous was filled by the player
        filled = filledByPlayer(wordPlayed.x, wordPlayed.y, a, b, wordPlayed.words, board);
         //Checks if there is a match between the chosen tile and the tile on the chosen coordinates
        if (!matchingTiles(handTile, board, a, b))
        {
            cout << "Chosen tile and chosen letter on the board do not match. \n";
            player.addTile(handTile);
        }
        //Checks if tile on the board has not been filled
        else if (forbiddenTile(handTile, board, a, b))
        {
            player.addTile(handTile);
            cout << "Tile already taken \n";
        }
        //Checks if the tiles previous to the one in coordinates (a, b) are filled
        else if (!isPreviousTileFilled(a, b, board))
        {
            player.addTile(handTile);
            cout << "Must choose a previous letter \n";
        }
        
        //Checks if any of the previous was filled by the player
        //filled = filledByPlayer(wordPlayed.x, wordPlayed.y, a, b, wordPlayed.words, board);
        //If any of the tiles of word was filled by the player and the chosen is not a first letter, the move is not valid
        else if (!firstLetter(a, b, board) && filled)
            {
                cout << "Move not valid \n";
                player.addTile(handTile);
            }
         
     } while(!matchingTiles(handTile, board, a, b) || forbiddenTile(handTile, board, a, b) || (!isPreviousTileFilled(a, b, board)) || (!firstLetter(a, b, board) && filled));
     
    
    //Set color attribute to red
    board.setTileRed(a, b);
    
    //Calculates player's score after the move
    calculateScore(a, b, board, player);
    
    clrscr();
    showBoard(board);

}

//---------------------------------------------------------------------------------
//Function for other turns
void otherTurns(Player &player, Board &board)
{
    int count = 0;
    map<string, char> possibleMoves = search(player, board, 2);
    if (!possibleMoves.empty())
        {   Word palavra = move(player, board, possibleMoves);
            possibleMoves = search(player, board, 3, palavra.words, palavra.x, palavra.y);
            count++;
            if (!possibleMoves.empty())
            {   anotherMove(player, board, palavra, possibleMoves); count++;}
            else
                exchangeTiles(player, board);
        }
    while(count)
    {
        addPoolTile(player, board);
        count--;
    }
    
}

//---------------------------------------------------------------------------------
//Determines current score of player
void calculateScore(size_t x, size_t y, Board &board, Player &player)
{
    vector<size_t> positions = board.getBoard().at(x).at(y).getPosition();
    vector<string> words = board.getBoard().at(x).at(y).belongsTo();
    vector<char> orientations = board.getBoard().at(x).at(y).getOrientation();
    
    //For the given coordinates (x,y) it analyses all letters of all the words it belongs to
    //When it reaches a black letter, the word is not complet. The additional score will be 0
    //Otherwise, additional score is 1
    int additional;
    
    for (size_t i = 0; i < positions.size(); i++)
        {
            additional = 1;
            switch (orientations.at(i))
            {
                case 'V':
                {
                    for (size_t pos = x - positions.at(i); pos < x + words.at(i).size() - positions.at(i); pos++)
                    { if (board.getBoard().at(pos).at(y).getColor() == "BLACK")
                        {
                            additional = 0;
                            break;
                        }
                    }
                }
                    break;
                case 'H':
                {
                    for (size_t pos = y - positions.at(i); pos < y + words.at(i).size() - positions.at(i); pos++)
                    { if (board.getBoard().at(x).at(pos).getColor() == "BLACK")
                        {
                            additional = 0;
                            break;
                        }
                    }
                }
                    break;
            }
            player.setScore(player.getScore() + additional);
        }
    

    cout << player.getName() << " your score is " << player.getScore() << endl;
            
}

//---------------------------------------------------------------------------------
//Determines the winner of the game
void whoWins(vector<Player> players)
{
    map<int, string> totalScores;
    
    for (auto x : players)
        totalScores.insert(pair<int, string> (x.getScore(), x.getName()));
    
    size_t pos = -1;
    cout << " Score   Name \n";
    for (auto x : totalScores)
    {   cout << setw(4) << x.first << setw(6) << x.second << endl;
        pos++;
    }
    
    cout << "Congratulations " << players.at(pos).getName() << " you won the game \n";
}

