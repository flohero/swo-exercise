//
// Created by florian on 09.01.21.
//

#include "bishop.h"

namespace chess {
  bishop::bishop(chess::color c) :
      chessman('b', c, false) {}

  void bishop::available_moves(chessman **figure_board, position pos,
                               int size, bool *movement_board) const {
    for(int i = static_cast<int>(direction::top_right); i < static_cast<int>(direction::end); i++) {
      bool stopped = false;
      direction dir{i};
      for(int j = 1; j < size && !stopped; j++) {
        position new_pos = pos
            .go_to(dir, j);
        if(!new_pos.is_in_matrix(size)) {
          stopped = true;
          continue;
        }
        int idx = new_pos.to_one_dimension(size);
        auto curr_figure = figure_board[idx];
        if(curr_figure == nullptr) {
          movement_board[idx] = true;
        } else {
          movement_board[idx] = curr_figure->figure_color() != this->figure_color();
          stopped = true;
        }
      }
    }
  }
}