//
// Created by florian on 20.12.20.
//

#include <iostream>
#include "rook.h"
#include "../position/direction.h"

namespace chess {
  void rook::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    for (int i = 0; i < 4; i++) {
      bool stopped = false;
      auto dir = direction{i};
      int until;
      switch (dir) {
        case direction::top:
          until = pos.y() + 1;
          break;
        case direction::left:
          until = pos.x() + 1;
          break;
        case direction::bottom:
          until = size - pos.y();
          break;
        case direction::right:
          until = size - pos.x();
          break;
        default:
          throw std::exception{};
      }
      for (int j = 1; j < until && !stopped; j++) {
        int index = pos
            .go_to(dir, j)
            .to_one_dimension(size);
        const auto curr_fig = figure_board[index];
        const auto is_not_figure = curr_fig == nullptr;
        if (is_not_figure) {
          movement_board[index] = true;
        } else {
          movement_board[index] = curr_fig->figure_color() != this->figure_color();
          stopped = true;
        }
      }
    }
  }

  rook::rook(color c) :
      chessman('r', c, false) {

  }
}
