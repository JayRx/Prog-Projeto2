#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale>         // std::locale, std::toupper

#include "board.hpp"

using namespace std;

// Creates a new Instance of a Board Class
Board createBoard(){
  int width = 0, height = 0;

  while(width <= 0 || width > 20 || height <= 0 || height > 20) {
    cout << "Board size (NxM): ";

    cin >> width;
    cin.ignore(1);
    cin >> height;

    if(width <= 0 || width > 20 || height <= 0 || height > 20)
      cout << "Invalid Board size!" << endl;
  }

  return Board(width, height);
}

// Reads the words from a text file ("words.txt") and stores them in a vector
vector<string> readWordsFromFile(){
  ifstream in_stream;
  string line;
  vector<string> words;

  in_stream.open("words.txt");
  while(getline(in_stream, line)) {
    words.push_back(line);
  }
  in_stream.close();

  return words;
}

// Write all the word instances of the class Word in a Board to a new text file ("board.txt")
// First line is the board size (M x N)
// Then writes the words following the format:  Aa H WORD
void writeToFile(Board *board) {
  int i;
  vector<Word> *words;
  ofstream of_stream;

  words = board->getWords();

  of_stream.open("board.txt");

  of_stream << board->getWidth() << " x " << board->getHeight() << endl;

  for(i = 0; i < words->size(); i++) {
    // Writes Word to File
    of_stream << words->at(i).getPosition()[0] << words->at(i).getPosition()[1] << " " << words->at(i).getOrientation() << " " << words->at(i).getValue() << endl;
  }

  of_stream.close();
}

// Get the position in numbers from a position in chars
int* positionFromLettersToNums(char *position) {
  int *pos, aux;

  pos = (int *) malloc(2 * sizeof(int));

  aux = (int) position[0];
  pos[0] = aux - 65;

  aux = (int) position[1];
  pos[1] = aux - 97;

  return pos;
}

// Checks if the position is valid (if the board has this position)
bool isPositionValid(Board *board, int *position) {
  if(position[0] >= board->getHeight())
    return false;

  if(position[1] >= board->getWidth())
    return false;

  return true;
}

// Handles the input to place a new word and calls Board's placeWord
bool placeWordHandler(Board *board, string word) {
  char position[2];
  char orientation;
  int* pos;
  bool aux;

  cout << "Word: " << word << endl;

  cout << "Word Position (Ex: Aa): ";
  cin >> position[0] >> position[1];
  pos = positionFromLettersToNums(position);
  if(!isPositionValid(board, pos)) {
    cout << "Invalid Position!" << endl;
    return false;
  }

  cout << "Word Orientation ('H' or 'V'): ";
  cin >> orientation;

  aux = (*board).placeWord(word, pos, orientation);

  free(pos);

  return aux;
}

// Binary Search of a string in a vector
int binarySearch(vector<string> arr, string x, int n) {
  int l = 0 ;
  int r = n - 1;

  while (l <= r) {
    int m = l + (r - l) / 2;
    int res;

    res = x.compare(arr.at(m));

    if (res == 0)
      return m;

    // If x greater, ignore left half
    if (res > 0)
      l = m + 1;

    // If x is smaller, ignore right half
    else
      r = m - 1;
  }

  return -1;
}

// Transforms all chars from a word to uppercase
string wordToUpperCase(string word) {
  char c;

  for(int i = 0; i < word.length(); i++) {
    c = word.at(i);
    if( c >= 'a' && c <= 'z')
      word.at(i) =  c - ('a' - 'A');
  }

  return word;
}

// Handles all the programs loop
// In each iteration:
//    Asks for a word and checks if the words vector has it
//    If the word is valid then changes all it's chars to uppercase
//    Then tries to place the word in the board
//    At last, prints the current state of the Board
int askForWords(Board *board, vector<string> words) {
  bool wordPlaced = false;
  string word;
  int pos = -1;

  do {
    do {
      wordPlaced = false;

      cout << "Enter Word (Enter 'q' to quit): ";
      cin >> word;

      if(word == "q") {
        return 0;
      }

      pos = binarySearch(words, word, words.size());

      if(pos == -1) {
        cout << "Invalid Word!" << endl;
        continue;
      }

      word = wordToUpperCase(word);

      wordPlaced = placeWordHandler(board, word);
      if(!wordPlaced) {
        cout << "Can't place Word!" << endl;
      }
    } while(!wordPlaced);
    board->printTable();
  } while(true);

  return 0;
}

// Main Function
int main() {
  Board board;
  vector<string> words;
  bool wordPlaced = false;

  // Create Board
  board = createBoard();

  // Print Board
  board.printTable();

  // Get Words from File
  words = readWordsFromFile();

  // Do all the word placing logic
  askForWords(&board, words);

  // Write the places words to the output file
  writeToFile(&board);

  return 0;
}
