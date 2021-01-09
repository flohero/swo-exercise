//
// Created by florian on 20.12.20.
//

#include <iostream>
#include <iomanip>
#include "chessboard.h"
#include "./chessboard_exception.h"
#include "../chesspiece/rook.h"
#include "../chesspiece/pawn.h"

#define MIN_CHESS_SIZE 8
#define SEPARATOR "|"

namespace chess {
  chess::chessboard::chessboard() :
      chessboard{MIN_CHESS_SIZE} {
  }

  chessboard::chessboard(int size) :
      size{size} {
    if (this->size < MIN_CHESS_SIZE) {
      throw chessboard_exception("Minimum size was undercut");
    }

    this->figure_board = new chessman *[static_cast<unsigned long>(size * size)]{nullptr};
    this->movement_board = new bool[static_cast<unsigned long>(size * size)]{false};
    for (int i = 0; i < this->size; i++) {
      this->figure_board[i] = new rook(color::white);
      this->figure_board[this->size * this->size - i - 1] = new rook(color::black);
      this->figure_board[this->size * this->size - this->size - i - 1] = new rook(color::black);
    }
    this->figure_board[27] = new rook(color::white);
    this->selected_index = 3;
    this->update_movement_board();
  }

  chessboard::~chessboard() {
    for (int i = 0; i < this->size * this->size; i++) {
      delete this->figure_board[i];
    }
    delete[] this->figure_board;
    delete[] this->movement_board;
  }

  void chessboard::update_movement_board() {
    auto current_figure = this->figure_board[this->selected_index];
    current_figure->available_moves(this->figure_board,
                                    position{this->selected_index % this->size, this->selected_index / this->size},
                                    this->size, movement_board);
  }

  void chessboard::print() const {
    int padding = static_cast<int>((" " + std::to_string(this->size)).length()) + 1;
    bool field = true;
    this->print_x_axis(padding);
    for (int i = 0; i < this->size * this->size; i++) {
      bool is_selected = (i == this->selected_index);
      if (i % this->size == 0) {
        // Separator Line
        this->print_line(padding);
        // Left side of axis
        this->print_y_axis_at(this->size - i / this->size);
      }
      std::cout << SEPARATOR;
      print_cell(i, field ? color::white : color::black, is_selected, this->movement_board[i]);
      field = !field;
      if ((i + 1) % this->size == 0) {
        field = !field;
        std::cout << SEPARATOR;
        if (i > 0) {
          // Right side y-axis
          this->print_y_axis_at(this->size - (i + 1 - this->size) / this->size);
        }
      }
    }
    print_line(padding);
    print_x_axis(padding);
  }

  void chessboard::print_cell(const int figure, const color field_color,
                              const bool selected, const bool in_path) const {
    std::string field_char = field_color == color::white ? "█" : " ";
    std::cout << (selected ? ">" : (in_path ? "[" : field_char));
    if (this->figure_board[figure] != nullptr) {
      std::cout << *this->figure_board[figure];
    } else {
      std::cout << field_char;
    }
    std::cout << (selected ? "<" : (in_path ? "]" : field_char));
  }

  void chessboard::print_line(const int padding) const {
    std::cout << std::endl;
    left_padding(padding);
    for (int j = 0; j < size; j++) {
      std::cout << "+---";
    }
    std::cout << "+" << std::endl;
  }

  void chessboard::print_x_axis(const int padding) const {
    left_padding(padding);
    std::cout << SEPARATOR;
    for (int i = 0; i < this->size; i++) {
      if (i != 0) {
        std::cout << " ";
      }
      std::cout << " " << char('a' + i) << " ";
    }
    std::cout << SEPARATOR;
  }

  void chessboard::print_y_axis_at(const int i) const {
    int max_length = static_cast<int>(std::to_string(this->size).length()) + 1;
    std::cout << std::setfill(' ') << std::setw(max_length) << i << " ";
  }

  void chessboard::left_padding(const int padding) {
    std::cout << std::string(static_cast<unsigned long>(padding), ' ');
  }
}
