//
// Created by florian on 06.01.21.
//

#pragma once

#include "position.h"

namespace chess {
  class position_path {
  public:
    explicit position_path(position *positions, int size);

    ~position_path();

  private:
    position *positions;
    int size;
  };
}

