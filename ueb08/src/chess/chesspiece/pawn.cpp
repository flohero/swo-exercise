//
// Created by florian on 09.01.21.
//

#include "pawn.h"

namespace chess {
  pawn::pawn(chess::color c) :
      chessman('p', c, false) {}

  void pawn::available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const {
    direction dir = this->figure_color() == color::white ? direction::bottom : direction::top;
    color enemy = this->figure_color() == color::white ? color::black : color::white;
    const position &bot_pos = pos
        .go_to(dir, 1);
    int index = bot_pos
        .to_one_dimension(size);
    if (!bot_pos.is_in_matrix(size)) {
      return;
    }
    // If the field in front of the pawn is empty
    if (figure_board[index] == nullptr) {
      movement_board[index] = true;
      int nextIndex = pos
          .go_to(dir, 2)
          .to_one_dimension(size);
      // If the figure was never moved a pawn is allowed to move 2 fields
      movement_board[nextIndex] = !this->moved && figure_board[nextIndex] == nullptr;
    }
    for (int side = static_cast<int>(direction::right);
         side < static_cast<int>(direction::top_right);
         side++) {
      int hit_index = bot_pos
          .go_to(direction{side}, 1)
          .to_one_dimension(size);
      movement_board[hit_index] =
          figure_board[hit_index] != nullptr && figure_board[hit_index]->figure_color() == enemy;
    }
  }
}