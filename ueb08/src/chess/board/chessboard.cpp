//
// Created by florian on 20.12.20.
//

#include <iostream>
#include <iomanip>
#include <functional>
#include <random>
#include "chessboard.h"
#include "./chessboard_exception.h"
#include "../chessman_factory.h"

#define MIN_CHESS_SIZE 8
#define MAX_CHESS_SIZE 26
#define SEPARATOR "|"

namespace chess {
  // In which frequency a chess board should be initialized
  const std::string chessboard::chessman_freq = "rnbqkbnr";

  chessboard::chessboard() :
      chessboard{MIN_CHESS_SIZE} {
  }

  chessboard::chessboard(int size) :
      size{size} {
    if (this->size < MIN_CHESS_SIZE) {
      throw chessboard_exception{"Minimum size was undercut"};
    }
    if (this->size > MAX_CHESS_SIZE) {
      throw chessboard_exception{"Size is bigger than maximum size of 26"};
    }

    this->figure_board = new chessman *[static_cast<unsigned long>(size * size)]{nullptr};
    this->movement_board = new bool[static_cast<unsigned long>(size * size)]{false};
    this->init_board(color::white);
    this->init_board(color::black);
  }

  chessboard::~chessboard() {
    for (int i = 0; i < this->size * this->size; i++) {
      delete this->figure_board[i];
    }
    delete[] this->figure_board;
    delete[] this->movement_board;
  }

  void chessboard::init_board(color c) {
    int start = c == color::white ? 0 : this->size * this->size - this->size;
    chessman_factory factory{c};
    // pawns
    for (int i = 0; i < this->size; i++) {
      position pos{i, c == color::white ? 1 : this->size - 2};
      const int idx = pos.to_one_dimension(this->size);
      figure_board[idx] = factory.produce_chessman(chessman_type::pawn);
    }
    int idx = 0;
    std::string long_freq;
    for(int i = 0; i < this->size; i++) {
      char char_at = chessboard::chessman_freq.at(static_cast<unsigned long>(i) % chessboard::chessman_freq.length());
      long_freq.push_back(char_at);
    }
    for (char type: long_freq) {
      figure_board[start + idx++] = factory.produce_chessman(chessman_type{type});
    }
  }

  void chessboard::select(const position &pos, const color c) {
    int idx = pos.to_one_dimension(this->size);

    if (!pos.is_in_matrix(this->size)) {
      throw chessboard_exception{"Not a valid position"};
    }
    auto curr_figure = this->figure_board[idx];
    if (curr_figure == nullptr) {
      throw chessboard_exception{"No chesspiece on this position"};
    }
    if (curr_figure->figure_color() != c) {
      throw chessboard_exception{"Your color and color of chesspiece do not match"};
    }
    this->selected_index = idx;
    this->update_movement_board();
    if (get_movable_count() == 0) {
      throw chessboard_exception{"No movements available"};
    }
  }

  /**
   * Unselect the current figure.
   * The movement_board will be updated
   */
  void chessboard::unselect() {
    this->selected_index = -1;
    update_movement_board();
  }

  /**
   * @return the count of available fields a figure can move to
   */
  int chessboard::get_movable_count() const {
    int movement_count = 0;
    for (int i = 0; i < size * size; i++) {
      if (movement_board[i]) {
        movement_count++;
      }
    }
    return movement_count;
  }


  /**
   * Moves an already selected figure to a position.
   * If there is an enemy figure on the destination position it will be killed.
   * @param pos the destination position
   * @returns if an essential enemy figure was hit
   */
  chessman *chessboard::move_to(const position &pos) {
    chessman *killed = nullptr;
    if (!pos.is_in_matrix(this->size)) {
      throw chessboard_exception{"Not a valid position"};
    }
    int idx = pos.to_one_dimension(this->size);
    if (!this->movement_board[idx]) {
      throw chessboard_exception{"Not a valid position"};
    }
    auto figure = this->figure_board[idx];

    if (figure != nullptr) {
      killed = this->figure_board[idx];
      this->figure_board[idx] = nullptr;
    }
    this->figure_board[this->selected_index]->move();
    this->figure_board[idx] = this->figure_board[this->selected_index];
    this->figure_board[this->selected_index] = nullptr;
    unselect();
    return killed;
  }

  /**
   * Selects a random movable figure matching the provided color
   * @param c which color the figure should have
   */
  void chessboard::select_random_movable_figure(const color &c) {
    // count figures of color c
    auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
    bool found = false;
    for (int i = 0; !found; i++) {
      this->unselect();
      int new_idx = i % (this->size * this->size);
      if (this->figure_board[new_idx] != nullptr
          && this->figure_board[new_idx]->figure_color() == c) {
        this->selected_index = new_idx;
        this->update_movement_board();
        if (this->get_movable_count() > 0 && gen()) {
          this->selected_index = new_idx;
          found = true;
        }
      }
    }
  }

  chessman *chessboard::move_random() {
    bool found_move = false;
    update_movement_board();
    auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
    int idx = 0;
    for (int i = 0; !found_move; i++) {
      if (this->movement_board[i % (this->size * this->size)]) {
        if (gen()) {
          idx = i % (this->size * this->size);
          found_move = true;
        }
      }
    }
    chessman *killed = nullptr;
    auto figure = this->figure_board[idx];

    if (figure != nullptr) {
      killed = this->figure_board[idx];
      this->figure_board[idx] = nullptr;
    }
    this->figure_board[this->selected_index]->move();
    this->figure_board[idx] = this->figure_board[this->selected_index];
    this->figure_board[this->selected_index] = nullptr;
    unselect();
    return killed;
  }

  void chessboard::update_movement_board() {
    if (this->selected_index == -1) {
      for (int i = 0; i < this->size * this->size; i++) {
        movement_board[i] = false;
      }
    } else {
      auto current_figure = this->figure_board[this->selected_index];
      current_figure->available_moves(this->figure_board,
                                      position{this->selected_index % this->size, this->selected_index / this->size},
                                      this->size, movement_board);
    }
  }

  /* Print Methods*/

  void chessboard::print() const {
    int padding = static_cast<int>((" " + std::to_string(this->size)).length()) + 1;
    bool field = true;
    std::cout << std::endl;
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
    std::cout << std::endl;
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
      std::cout << " " << char('A' + i) << " ";
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
