//
// Created by florian on 09.01.21.
//

#pragma once

#include "chessman.h"

namespace chess {
  class pawn: public chessman {

  public:
    explicit pawn(color c);

    void available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const override;
  };
}

