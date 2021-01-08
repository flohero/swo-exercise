//
// Created by florian on 20.12.20.
//

#pragma once

#include "chessman.h"

namespace chess {
  class rook: public chessman {
  public:
    position_path *available_moves(position &start, position &end) override;

  private:

  };
}

