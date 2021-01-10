//
// Created by florian on 09.01.21.
//

#include "pawn.h"

namespace chess {
  pawn::pawn(chess::color c) :
      chessman(chessman_type::pawn, c, false) {}

  void pawn::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    direction dir = this->fig_color_ == color::white ? direction::bottom : direction::top;
    color enemy = this->fig_color_ == color::white ? color::black : color::white;
    const position &bot_pos = pos
        .go_to(dir, 1);
    int index = bot_pos
        .to_one_dimension(size);
    // If next position is not in matrix, the pawn is at the other side of the board
    if (!bot_pos.is_in_matrix(size)) {
      return;
    }
    // If the field in front of the pawn is empty
    if (figure_board[index] == nullptr) {
      movement_board[index] = true;
      const position &next_pos = pos
          .go_to(dir, 2);
      if (next_pos.is_in_matrix(size)) {
        int next_idx = next_pos
            .to_one_dimension(size);
        // If the figure was never moved a pawn is allowed to move 2 fields
        movement_board[next_idx] = !this->moved && figure_board[next_idx] == nullptr;
      }
    }
    for (int side = static_cast<int>(direction::right);
         side < static_cast<int>(direction::top_right);
         side++) {
      const position &hit_pos = bot_pos
          .go_to(direction{side}, 1);
      if (!hit_pos.is_in_matrix(size)) {
        continue;
      }
      int hit_index = hit_pos
          .to_one_dimension(size);
      movement_board[hit_index] =
          figure_board[hit_index] != nullptr && figure_board[hit_index]->figure_color() == enemy;
    }
  }
}