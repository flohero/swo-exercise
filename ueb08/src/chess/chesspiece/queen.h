//
// Created by florian on 09.01.21.
//

#pragma once

#include "../color.h"
#include "chessman.h"

namespace chess {
  class queen : public chessman{
  public:
    explicit queen(color c);

    void available_moves(chessman **figure_board, position pos, int size, bool *movement_board) const override;
  };
}

