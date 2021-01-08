//
// Created by florian on 20.12.20.
//

#pragma once

#include "position_path.h"

namespace chess {
  /**
   * Represents a position a chessfigure can be on or move to.
   */
  class position {
  public:
    position() {
      x = y = 0;
    };

    position(int x, int y);

    position operator+(const position &pos) const;

    position operator-(const position &pos) const;

    bool operator==(const position &pos) const;

    [[nodiscard]] position_path path_to(const position &end) const;

  protected:
    int x;
    int y;

  };
}

