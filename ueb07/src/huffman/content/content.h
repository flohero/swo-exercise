//
// Created by florian on 12.12.20.
//

#pragma once

#include "../bit_stream/bit_stream.h"
#include "../bit_stream/bit_string_stream.h"

namespace huffman {
  /**
   * Abstract class to represent a file content
   */
  class content {
    public:
      content() = default;

      /**
       * Initialize a bit_string_stream from a file path
       * @param file a file path
       */
      explicit content(const std::string& file) {
        this->stream = new bit_string_stream(file);
      }

      ~content() {
        delete this->stream;
      };

      /**
       * Encode a file
       * @returns encoded content of a file
       */
      [[nodiscard]] virtual std::string encode() const = 0;

      /**
       * Decode a string
       * @param encoded the encoded string
       * @returns the decoded string
       */
      [[nodiscard]] virtual std::string decode(std::string encoded) const = 0;

    protected:

      /**
       * Representation of a file
       */
      bit_stream *stream = nullptr;
  };
}

