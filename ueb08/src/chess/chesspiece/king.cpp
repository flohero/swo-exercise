//
// Created by florian on 09.01.21.
//

#include "king.h"

namespace chess {
  king::king(chess::color c) :
      chessman('k', c, true) {}

  void king::available_moves(chessman **figure_board, position pos,
                             int size, bool *movement_board) const {
    for (int i = static_cast<int>(direction::start);
         i < static_cast<int>(direction::end); i++) {
      auto new_pos = pos.go_to(direction{i}, 1);
      if(!new_pos.is_in_matrix(size)) {
        continue;
      }
      const int idx = new_pos.to_one_dimension(size);
      auto curr_figure = figure_board[idx];
      if(curr_figure == nullptr) {
        movement_board[idx] = true;
      } else {
        movement_board[idx] = curr_figure->figure_color() != this->fig_color_;
      }
    }
  }
}