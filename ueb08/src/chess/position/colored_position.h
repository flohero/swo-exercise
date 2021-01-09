//
// Created by florian on 09.01.21.
//

#pragma once

#include "../color.h"
#include "position.h"

namespace chess {
  class colored_position {
  public:
    colored_position()= default;
    colored_position(position pos, color field_color);

    color field_color();

    position pos();

  private:
    position pos_ = position{0, 0};
    color field_color_ = color::none;
  };
}

