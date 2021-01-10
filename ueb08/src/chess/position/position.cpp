//
// Created by florian on 20.12.20.
//

#include "position.h"

namespace chess {
  position::position(int x, int y) :
      x_{x}, y_{y} {
  }


  bool position::operator==(const position &pos) const {
    return this->x_ == pos.x_ && this->y_ == pos.y_;
  }

  /**
   * Calculate the position in an array
   * @param offset size of matrix
   * @return the index in an array
   */
  int position::to_one_dimension(const int offset) const {
    return this->x_ + this->y_ * offset;
  }

  /**
   * Check if position is in a matrix
   * @param size x and y axis
   * @return if the position is in a matrix
   */
  bool position::is_in_matrix(const int size) const {
    return this->x_ >= 0 && this->y_ >= 0 && this->x_ < size && this->y_ < size;
  }

  /**
   * Move the position in a specific direction,
   * can be done multiple times
   * @param dir which direction
   * @param times how often
   * @return a new position
   */
  position position::go_to(const direction dir, const int times) const {
    position new_pos{*this};
    switch (dir) {
      case direction::top:
        new_pos.y_ -= times;
        break;
      case direction::right:
        new_pos.x_ += times;
        break;
      case direction::bottom:
        new_pos.y_ += times;
        break;
      case direction::left:
        new_pos.x_ -= times;
        break;
      case direction::top_right:
        new_pos.x_ += times;
        new_pos.y_ -= times;
        break;
      case direction::bottom_right:
        new_pos.x_ += times;
        new_pos.y_ += times;
        break;
      case direction::bottom_left:
        new_pos.x_ -= times;
        new_pos.y_ += times;
        break;
      case direction::top_left:
        new_pos.x_ -= times;
        new_pos.y_ -= times;
        break;
      case direction::end:
        break;
    }
    return new_pos;
  }
}
