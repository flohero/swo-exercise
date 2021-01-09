//
// Created by florian on 20.12.20.
//

#pragma once

#include "direction.h"

namespace chess {
  /**
   * Represents a position a chessfigure can be on or move to.
   */
  class position {
  public:
    position() : x_{0}, y_{0} {};

    position(const position &pos) = default;

    position(int x, int y);

    [[nodiscard]] int to_one_dimension(int offset) const;

    [[nodiscard]] bool is_in_matrix(int size) const;

    [[nodiscard]] position go_to(direction dir, int times) const;

    bool operator==(const position &pos) const;

    [[nodiscard]] int x() const {
      return x_;
    }

    [[nodiscard]] int y() const {
      return y_;
    }

  private:
    int x_;
    int y_;
  };
}

