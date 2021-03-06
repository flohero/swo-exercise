//
// Created by florian on 20.12.20.
//

#pragma once

#include <ostream>
#include "../position/position.h"
#include "../color.h"
#include "chessman_type.h"

namespace chess {
  class chessman {
  public:
    chessman(chessman_type symbol, color fig_color, bool essential);

    virtual ~chessman() = default;

    virtual void available_moves(chessman **figure_board, position pos,
                                 int size, bool *movement_board) const = 0;


    [[nodiscard]] color figure_color() const;

    [[nodiscard]] bool is_essential() const;

    void move();

    friend std::ostream &operator<<(std::ostream &os, const chessman &man);

  protected:
    bool moved = false;

    const color fig_color_;

    void common_movements(chessman **figure_board, position pos,
                          int size, bool *movement_board, direction start, direction end) const;

  private:
    const chessman_type symbol_;
    const bool essential_;

  };

  std::ostream &operator<<(std::ostream &os, const chessman &man);
}

