//
// Created by florian on 12.12.20.
//

#pragma once

#include <utility>

#include "bit_stream.h"

namespace huffman {
  class default_stream: public bit_stream {
    public:
      explicit default_stream(std::string value) {
        this->value = std::move(value);
      }

      std::string content() const override {
        return this->value;
      }

    private:
      std::string value;
  };
}

