//
// Created by florian on 20.12.20.
//

#include "chessman.h"

namespace chess {
  chessman::chessman(const chessman_type symbol, const color fig_color, bool essential) :
      symbol_{symbol}, fig_color_{fig_color}, essential_{essential} {
  }

  color chessman::figure_color() const {
    return this->fig_color_;
  }

  bool chessman::is_essential() const {
    return this->essential_;
  }

  std::ostream &operator<<(std::ostream &os, const chess::chessman &man) {
    char sym = static_cast<char>(man.symbol_);
    return os << char(man.fig_color_ == color::white
                      ? toupper(sym)
                      : tolower(sym));
  }

  void chessman::move() {
    this->moved = true;
  }

  void chessman::common_movements(chessman **figure_board, position pos,
                                  int size, bool *movement_board,
                                  direction start, direction end) const {
    for (int i = static_cast<int>(start); i < static_cast<int>(end); i++) {
      bool stopped = false;
      direction dir{i};
      for (int j = 1; j < size && !stopped; j++) {
        position new_pos = pos
            .go_to(dir, j);
        if (!new_pos.is_in_matrix(size)) {
          stopped = true;
          continue;
        }
        int idx = new_pos.to_one_dimension(size);
        auto curr_figure = figure_board[idx];
        if (curr_figure == nullptr) {
          movement_board[idx] = true;
        } else {
          movement_board[idx] = curr_figure->fig_color_ != this->fig_color_;
          stopped = true;
        }
      }
    }
  }
}