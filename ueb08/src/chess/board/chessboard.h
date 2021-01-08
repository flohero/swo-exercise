//
// Created by florian on 20.12.20.
//

#pragma once

#include "../chesspiece/chessman.h"

namespace chess {
  class chessboard {
  public:
    chessboard();

    explicit chessboard(unsigned int size);

    ~chessboard();

  private:
    chessman **figures;
    unsigned int size;
  };
}

