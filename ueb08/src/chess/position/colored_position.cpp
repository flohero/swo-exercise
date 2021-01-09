//
// Created by florian on 09.01.21.
//

#include "colored_position.h"

namespace chess {
  colored_position::colored_position(position pos, color field_color) :
      pos_{pos}, field_color_{field_color} {}

  color colored_position::field_color() {
    return this->field_color_;
  }

  position colored_position::pos() {
    return this->pos_;
  }
}