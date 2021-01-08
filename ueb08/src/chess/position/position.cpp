//
// Created by florian on 20.12.20.
//

#include <exception>
#include <cstdlib>
#include "position.h"
#include "position_path.h"

namespace chess {
  position::position(int x, int y) {
    this->x = x;
    this->y = y;
  }

  position position::operator+(const position &pos) const {
    return position(this->x + pos.x, this->y + pos.y);
  }

  position position::operator-(const position &pos) const {
    return position(this->x - pos.x, this->y - pos.y);
  }

  bool position::operator==(const position &pos) const {
    return this->x == pos.x && this->y == pos.y;
  }

  /**
   * Construct a path from a starting position and a destination position.
   * The start and dest must form a vector which has an angle of 45° degrees or its multiples.
   * The resulting path will be exclusive the starting position.
   * @param start
   * @param dest
   * @throws position_path_exception if the vector is not a multiples of a 45° degree angle
   */
  position_path position::path_to(const position &end) const {
    int vec_x = end.x - this->x,
        vec_y = end.y - this->y;
    if (*this == end // the positions are not the same
        || (vec_y != vec_x // if vec_y == vec_y then the vector is diagonal
            && (vec_x != 0 && vec_y != 0)
        )) {
      throw std::exception{};
    }
    int inc_x = 0,
        inc_y = 0;
    if (std::abs(vec_x) == std::abs(vec_y)) {
      inc_x = vec_x / std::abs(vec_x);
      inc_y = vec_y / std::abs(vec_y);
    } else if (vec_x == 0) {
      inc_y = vec_y / std::abs(vec_y);
    } else {
      inc_x = vec_x / std::abs(vec_x);
    }

    int size = vec_x != 0 ? std::abs(vec_x) : std::abs(vec_y);
    auto *positions = new position[static_cast<unsigned long>(size)];
    for (int i = 0; i < size; i++) {
      const int inc_by = i + 1;
      positions[i] = position{this->x + (inc_x * inc_by),
                              this->y + (inc_y * inc_by)};
    }
    return position_path{positions, size};
  }
}
