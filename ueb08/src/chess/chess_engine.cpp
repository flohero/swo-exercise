//
// Created by florian on 09.01.21.
//

#include <iostream>
#include <ctime>
#include <thread>
#include "chess_engine.h"
#include "board/chessboard_exception.h"
#include "play_mode.h"

#define MIN_CHESS_SIZE 8

#define WAIT_TIME 2000
namespace chess {
  chess_engine::chess_engine() :
      chess_engine{MIN_CHESS_SIZE} {}

  chess_engine::chess_engine(int size) :
      size{size}, board{this->size} {
  }

  void chess_engine::loop() {
    bool ended = false;
    play_mode mode = chess_engine::splash_screen();
    while (!ended) {
      board.print();
      std::cout << get_current_player() << std::endl;
      if(mode == play_mode::player) {
        select_figure();
      } else {
        this->board.select_random_movable_figure(this->player);
        computer_wait();
      }
      board.print();
      std::cout << get_current_player() << std::endl;
      chessman *killed = nullptr;
      if(mode == play_mode::player) {
        killed = this->move_figure();
      } else {
        killed = this->board.move_random();
        computer_wait();
      }
      if (killed != nullptr && killed->is_essential()) {
        ended = true;
        std::cout << this->get_current_player() << " won!";
      } else {
        this->switch_player();
      }
      delete killed;
    }
  }

  void chess_engine::computer_wait() { std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME)); }

  play_mode chess_engine::splash_screen() {
    std::cout << "   |\\_       Welcome to Chess" << std::endl
              << "  /  .\\_     King:   " << static_cast<char>(chessman_type::king) << std::endl
              << " |   ___)    Queen:  " << static_cast<char>(chessman_type::queen) << std::endl
              << " |    \\      Bishop: " << static_cast<char>(chessman_type::bishop) << std::endl
              << " |  =  |     Knight: " << static_cast<char>(chessman_type::knight) << std::endl
              << " /_____\\     Rook:   " << static_cast<char>(chessman_type::rook) << std::endl
              << "[_______]    Pawn:   " << static_cast<char>(chessman_type::pawn) << std::endl
              << std::endl
              << "Insert Play Mode (0) Player VS Player (1) Computer VS Computer:" << std::endl;
    bool success = false;
    play_mode mode;
    while (!success) {
      std::string mode_str;
      std::cin >> mode_str;
      try {
        int mode_int = std::stoi(mode_str);
        if (mode_int != 0 && mode_int != 1) {
          throw std::invalid_argument{"Not a valid argument!"};
        }
        mode = play_mode{mode_int};
        success = true;
      } catch (std::invalid_argument const &e) {
        std::cout << "Not a valid input" << std::endl;
        continue;
      }
      catch (std::out_of_range const &e) {
        std::cout << "Not a valid input" << std::endl;
        continue;
      }
    }
    return mode;
  }

  std::string chess_engine::get_current_player() const {
    return player == color::white ? "Player White" : "Player Black";
  }

  void chess_engine::select_figure() {
    bool selected = false;
    while (!selected) {
      position pos = input_position();
      try {
        board.select(pos, this->player);
        selected = true;
      } catch (chessboard_exception &e) {
        std::cout << e.what() << std::endl;
      }
    }
  }

  chessman *chess_engine::move_figure() {
    bool selected = false;
    chessman *killed;
    while (!selected) {
      position pos = input_position();
      try {
        killed = board.move_to(pos);
        selected = true;
      } catch (chessboard_exception &e) {
        std::cout << e.what() << std::endl;
      }
    }
    return killed;
  }

  void chess_engine::switch_player() {
    player = this->player == color::white ? color::black : color::white;
  }

  static const char *const not_a_valid_pos = "Not a valid position try again!";

  position chess_engine::input_position() const {
    bool success = false;
    position pos;
    while (!success) {
      std::string coord;
      std::cout << "Input coordinates (Example: C4):" << std::endl;
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
        pos = position{x - 'A', this->size - y};
        if (!pos.is_in_matrix(size)) {
          throw std::invalid_argument{not_a_valid_pos};
        }
      } catch (std::invalid_argument const &e) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      catch (std::out_of_range const &e) {
        std::cout << not_a_valid_pos << std::endl;
        continue;
      }
      success = true;
    }
    return pos;
  }
}
