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

  int position::to_one_dimension(const int offset) const {
    return this->x_ + this->y_ * offset;
  }

  bool position::is_in_matrix(const int size) const {
    return this->x_ >= 0 && this->y_ >= 0 && this->x_ < size && this->y_ < size;
  }

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
    }
    return new_pos;
  }
}
