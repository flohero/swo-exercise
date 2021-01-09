//
// Created by florian on 09.01.21.
//

#include "queen.h"

namespace chess {
  queen::queen(chess::color c) :
      chessman{'q', c, false} {}

  void queen::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    this->common_movments(figure_board, pos, size, movement_board, direction::start, direction::end);
  }
}