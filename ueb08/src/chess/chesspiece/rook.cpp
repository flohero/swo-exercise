//
// Created by florian on 20.12.20.
//

#include "rook.h"

namespace chess {
  void rook::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    this->common_movements(figure_board, pos,
                           size, movement_board,
                           direction::start, direction::top_right);
  }

  rook::rook(color c) :
      chessman(chessman_type::rook, c, false) {
  }
}
