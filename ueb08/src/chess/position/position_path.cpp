//
// Created by florian on 06.01.21.
//

#include <exception>
#include "position_path.h"
#include "position.h"

namespace chess {
  position_path::position_path(position *positions, const int size) {
    this->positions = positions;
    this->size = size;
  }

  position_path::~position_path() {
    delete[] this->positions;
  }
}