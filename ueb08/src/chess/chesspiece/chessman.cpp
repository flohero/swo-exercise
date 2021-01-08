//
// Created by florian on 20.12.20.
//

#include "chessman.h"

namespace chess {
  chessman::chessman(const char symbol, const color fig_color) :
      symbol{symbol}, fig_color{fig_color} {
  }

  int chessman::available_moves_size() {
    return this->move_size;
  }

  std::ostream &operator<<(std::ostream &os, const chess::chessman &man) {
    return os << (man.fig_color == white
                  ? toupper(man.symbol)
                  : tolower(man.symbol));
  }
}