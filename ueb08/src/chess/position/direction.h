//
// Created by florian on 09.01.21.
//

#pragma once

namespace chess {
  enum class direction {
    top = 0,
    bottom = 1,
    right = 2,
    left = 3,
    top_right = 4,
    bottom_right = 5,
    bottom_left = 6,
    top_left = 7,
    start = top,
    end = top_left + 1,
  };
}

