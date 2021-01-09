//
// Created by florian on 20.12.20.
//

#include "chessman.h"

namespace chess {
  chessman::chessman(const char symbol, const color fig_color, bool essential) :
      symbol_{symbol}, fig_color_{fig_color}, essential_{essential} {
  }

  color chessman::figure_color() const {
    return this->fig_color_;
  }

  bool chessman::is_essential() const {
    return this->essential_;
  }

  std::ostream &operator<<(std::ostream &os, const chess::chessman &man) {
    return os << char(man.fig_color_ == color::white
                  ? toupper(man.symbol_)
                  : tolower(man.symbol_));
  }

  void chessman::move() {
    this->moved = true;
  }
}