//
// Created by florian on 09.01.21.
//

#include <iostream>
#include "chess_engine.h"
#include "board/chessboard_exception.h"

#define MIN_CHESS_SIZE 8

namespace chess {
  chess_engine::chess_engine() :
      chess_engine{MIN_CHESS_SIZE} {}

  chess_engine::chess_engine(int size) :
      board{size} {}

  void chess_engine::loop() {
    bool ended = false;
    bool gamer = true;
    board.print();
    do {
      position pos = input_position();
      try {
        board.select(pos, gamer ? color::white : color::black);
      } catch (chessboard_exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }
      board.print();
      pos = input_position();
      this->board.move_to(pos);
      board.print();
      gamer = false;
      ended = true;
    } while (!ended);
  }

  static const char *const not_a_valid_pos = "Not a valid position try again!";

  position chess_engine::input_position() {
    bool success = false;
    position pos;
    do {
      std::string coord;
      std::cout << "Input the coordinates of the chessfigure you'd like to pick up (Example: C4):" << std::endl;
      std::cin >> coord;
      if (coord.length() < 2) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      char x = static_cast<char>(toupper(coord.at(0)));
      if (!(x >= 'A' && x <= 'Z')) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      std::string y_str = coord.substr(1);
      int y;
      try {
        y = std::stoi(y_str);
      } catch (std::invalid_argument const &e) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      catch (std::out_of_range const &e) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      success = true;
      // TODO Counting in the wrong direction
      pos = position{x - 'A', y - 1};
    } while (!success);
    return pos;
  }
}
