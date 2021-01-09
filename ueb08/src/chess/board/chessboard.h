//
// Created by florian on 20.12.20.
//

#pragma once

#include "../chesspiece/chessman.h"

namespace chess {
  /**
   * Represents a chessboard.
   * White starts always on the top.
   */
  class chessboard {
  public:
    chessboard();

    explicit chessboard(int size);

    ~chessboard();

    void print() const;

  private:
    chessman **figure_board;
    bool *movement_board;
    int size;
    int selected_index = -1;

    void print_cell(int figure, color field_color, bool selected, bool in_path) const;

    void print_line(int padding) const;

    void print_x_axis(int padding) const;

    static void left_padding(int padding);

    void print_y_axis_at(int i) const;

    void update_movement_board();
  };
}

