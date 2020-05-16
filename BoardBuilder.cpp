#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.hpp"

#define ALPHABET_LETTES_NO 26

using namespace std;

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

void writeToFile(Board *board) {
  int i;
  vector<Word> *words;
  ofstream of_stream;

  words = board->getWords();

  of_stream.open("board.txt");

  of_stream << board->getWidth() << " x " << board->getHeight() << endl;

  for(i = 0; i < words->size(); i++) {
    of_stream << words->at(i).getPosition()[0] << words->at(i).getPosition()[1] << " " << words->at(i).getOrientation() << " " << words->at(i).getValue() << endl;
  }

  of_stream.close();
}

int* positionFromLettersToNums(char *position) {
  int *pos, aux;

  pos = (int *) malloc(2 * sizeof(int));

  aux = (int) position[0];
  pos[0] = aux - 65;

  aux = (int) position[1];
  pos[1] = aux - 97;

  return pos;
}

bool placeWordHandler(Board *board, string word) {
  char position[2];
  char orientation;
  int* pos;

  cout << "Word: " << word << endl;

  cout << "Word Position (Ex: Aa): ";
  cin >> position[0] >> position[1];
  pos = positionFromLettersToNums(position);

  cout << "Word Orientation ('H' or 'V'): ";
  cin >> orientation;

  return (*board).placeWord(word, pos, orientation);
}

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

int askForWords(Board *board, vector<string> words) {
  bool wordPlaced = false;
  string word;
  int pos = -1;

  do {
    do {
      wordPlaced = false;

      cout << "Input Word: ";
      cin >> word;

      if(word == "q") {
        return 0;
      }

      pos = binarySearch(words, word, words.size());

      if(pos == -1)
        continue;

      wordPlaced = placeWordHandler(board, words.at(pos));
    } while(!wordPlaced);
    board->printTable();
  } while(true);

  return 0;
}

int main() {
  Board board;
  vector<string> words;
  bool wordPlaced = false;

  board = createBoard();

  board.printTable();

  words = readWordsFromFile();

  askForWords(&board, words);

  writeToFile(&board);

  return 0;
}
