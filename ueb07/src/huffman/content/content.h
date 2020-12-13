//
// Created by florian on 12.12.20.
//

#pragma once

#include "../bit_stream/bit_stream.h"
#include "../bit_stream/bit_string_stream.h"

/**
 * Base class for encoding and decoding content.
 * Doesn't have to be the Huffman encoding.
 */
namespace huffman {
  class content {
    public:
      content() = default;

      explicit content(const std::string& file) {
        this->stream = new bit_string_stream(file);
      }

      ~content() {
        delete this->stream;
      };

      [[nodiscard]] virtual std::string encode() const = 0;
      [[nodiscard]] virtual std::string decode(std::string encoded) const = 0;

    protected:
      bit_stream *stream = nullptr;
  };
}

