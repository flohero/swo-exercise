//
// Created by florian on 08.12.20.
//

#pragma once

#include <string>

namespace huffman {
    class bit_stream {
      public:
        explicit bit_stream(std::string filename);

        virtual std::string load_file_content() const = 0;

      protected:
        std::string filename;
    };
}