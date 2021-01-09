//
// Created by florian on 09.01.21.
//

#pragma once

#include "chessman.h"

namespace chess {
  class knight: public chessman {
  public:
    explicit knight(color c);

    void available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const override;
  };
}

