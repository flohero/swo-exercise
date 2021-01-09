//
// Created by florian on 09.01.21.
//

#pragma once

#include "chessman.h"

namespace chess {
  class bishop: public chessman {
  public:
    explicit bishop(color c);

    void available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const override;
  };
}

