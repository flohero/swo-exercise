//
// Created by florian on 20.12.20.
//

#pragma once

#include <ostream>
#include "../position/position.h"
#include "../color.h"
#include "../position/position_path.h"

namespace chess {
  class chessman {
  public:
    chessman(char symbol, color fig_color);

    virtual position_path *available_moves(position &start, position &end) = 0;

    int available_moves_size();

    friend std::ostream &operator<<(std::ostream &os, const chessman &man);

  protected:
    const char symbol;
    const color fig_color;
    int move_size;

  };

  std::ostream &operator<<(std::ostream &os, const chessman &man);
}

