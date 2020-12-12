//
// Created by florian on 08.12.20.
//

#pragma once

#include <string>

namespace huffman {
    class bit_stream {
      public:
        explicit bit_stream() = default;
        explicit bit_stream(std::string filename);

        virtual ~bit_stream() = default;

        virtual std::string content() const = 0;
      protected:
        std::string filename;
    };
}