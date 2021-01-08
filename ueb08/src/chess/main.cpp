//
// Created by florian on 20.12.20.
//
#include "board/chessboard.h"

using namespace chess;

int main() {
  chessboard board{};
  position start{0, 0};
  position dest{7, 0};
  auto path = start.path_to(dest);
}
