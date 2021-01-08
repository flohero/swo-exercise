//
// Created by florian on 20.12.20.
//

#include "chessboard.h"
#include "./chessboard_exception.h"

#define CHESS_SIZE 8
#define MIN_CHESS_SIZE 4

namespace chess {
  chess::chessboard::chessboard() :
      chessboard{CHESS_SIZE} {
  }

  chessboard::chessboard(unsigned int size) :
      size{size} {
    if(size < MIN_CHESS_SIZE) {
      throw chessboard_exception("Minimum size was undercut");
    }

    this->figures = new chessman *[size * size];
  }

  chessboard::~chessboard() {
    delete [] this->figures;
  }
}
