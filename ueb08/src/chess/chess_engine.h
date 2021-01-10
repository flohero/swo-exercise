//
// Created by florian on 09.01.21.
//

#pragma once

#include "board/chessboard.h"
#include "play_mode.h"

#define MIN_CHESS_SIZE 8

namespace chess {
  class chess_engine {
  public:
    chess_engine();

    explicit chess_engine(int size);

    void loop();

  private:
    int size;

    chessboard board;

    color player = color::white;

    [[nodiscard]] position input_position() const;

    void select_figure();

    void switch_player();

    chessman *move_figure();

    [[nodiscard]] std::string get_current_player() const;

    static chess::play_mode splash_screen();

    static void computer_wait();
  };
}

