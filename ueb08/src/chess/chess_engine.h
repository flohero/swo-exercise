//
// Created by florian on 09.01.21.
//

#pragma once

#include "board/chessboard.h"

namespace chess {
  class chess_engine {
  public:
    chess_engine();

    explicit chess_engine(int size);

    void loop();

  private:
    chessboard board;

    position input_position();
  };
}

