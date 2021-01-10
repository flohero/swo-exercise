//
// Created by florian on 20.12.20.
//
#include <iostream>
#include "chess_engine.h"
#include "board/chessboard_exception.h"

using namespace chess;

int main(int argc, const char *argv[]) {
  int board_size = MIN_CHESS_SIZE;;
  if (argc == 2) {
    try {
      board_size = std::stoi(argv[1]);
    } catch (std::exception &e) {
      std::cout << "Not a number";
    }
  }
  try {
    chess_engine engine{board_size};
    engine.loop();
  } catch (chessboard_exception &e) {
    std::cout << e.what();
  }
}
