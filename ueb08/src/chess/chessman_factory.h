//
// Created by florian on 09.01.21.
//

#pragma once

#include "chesspiece/chessman.h"

namespace chess {
  class chessman_factory {
  public:

    explicit chessman_factory(color c);

    [[nodiscard]] chessman *produce_chessman(chessman_type type) const;

  private:
    color c;

    void change_color(color c);
  };
}

