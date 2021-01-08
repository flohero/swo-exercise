//
// Created by florian on 06.01.21.
//

#pragma once


#include <exception>
#include <string>
#include <utility>

namespace chess {
  class chessboard_exception : public std::exception {
  public:
    explicit chessboard_exception(std::string msg) : msg{std::move(msg)} {}

    [[nodiscard]] const char *what() const noexcept override {
      return msg.c_str();
    }

  private:
    std::string msg;
  };
}

