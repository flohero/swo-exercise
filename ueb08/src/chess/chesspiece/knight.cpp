//
// Created by florian on 09.01.21.
//

#include "knight.h"

namespace chess {
  knight::knight(chess::color c) :
      chessman(chessman_type::knight, c, false) {}

  void knight::available_moves(chessman **figure_board, position pos,
                               int size, bool *movement_board) const {
    for (int i = 0; i < 4; i++) {
      direction dir{i};
      position new_pos = pos
          .go_to(dir, 2);
      if (!new_pos.is_in_matrix(size)) {
        continue;
      }

      int start, end;
      if (dir == direction::top || dir == direction::bottom) {
        start = static_cast<int>(direction::right);
        end = static_cast<int>(direction::top_right);
      } else {
        start = static_cast<int>(direction::top);
        end = static_cast<int>(direction::right);
      }

      for (int j = start; j < end; j++) {
        auto diag_pos = new_pos
            .go_to(direction{j}, 1);
        if (diag_pos.is_in_matrix(size)) {
          int idx = diag_pos.to_one_dimension(size);
          auto curr_figure = figure_board[idx];
          if (curr_figure == nullptr) {
            movement_board[idx] = true;
          } else {
            movement_board[idx] = curr_figure->figure_color() != this->fig_color_;
          }
        }
      }
    }
  }
}