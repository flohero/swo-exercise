//
// Created by florian on 09.01.21.
//

#include "bishop.h"

namespace chess {
  bishop::bishop(chess::color c) :
      chessman('b', c, false) {}

  void bishop::available_moves(chessman **figure_board, position pos,
                               int size, bool *movement_board) const {
    this->common_movements(figure_board, pos,
                          size, movement_board, direction::top_right, direction::end);
  }
}