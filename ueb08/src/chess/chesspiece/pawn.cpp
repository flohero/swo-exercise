//
// Created by florian on 09.01.21.
//

#include <iostream>
#include "pawn.h"

namespace chess {
  pawn::pawn(chess::color c) :
      chessman('p', c, false) {}

  void pawn::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    int direction = this->figure_color() == color::white ? 1 : -1;
    color enemy = this->figure_color() == color::white ? color::black : color::white;
    int index = position{pos.x(), pos.y() + direction}
        .to_one_dimension(size);
    if (index >= size * size) {
      return;
    }
    // If the field in front of the pawn is empty
    if (figure_board[index] == nullptr) {
      movement_board[index] = true;
      int nextIndex = position{pos.x(), pos.y() + 2 * direction}
          .to_one_dimension(size);
      // If the figure was never moved a pawn is allowed to move 2 fields
      movement_board[nextIndex] = !this->moved && figure_board[nextIndex] == nullptr;
    }
    // Right side hit
    if (pos.x() - 1 >= 0) {
      int leftHitIndex = position{pos.x() - 1, pos.y() + direction}
          .to_one_dimension(size);
      movement_board[leftHitIndex] =
          figure_board[leftHitIndex] != nullptr && figure_board[leftHitIndex]->figure_color() == enemy;
    }
    // Left side hit
    if (pos.x() + 1 < size) {
      int rightHitIndex = position{pos.x() + 1, pos.y() + direction}
          .to_one_dimension(size);
      movement_board[rightHitIndex] =
          figure_board[rightHitIndex] != nullptr && figure_board[rightHitIndex]->figure_color() == enemy;
    }
  }
}