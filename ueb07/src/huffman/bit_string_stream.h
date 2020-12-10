//
// Created by florian on 08.12.20.
//

#pragma once

#include "bit_stream.h"

namespace huffman {
    class bit_string_stream : public bit_stream {
      public:
        explicit bit_string_stream(const std::string& filename);

        [[nodiscard]] std::string load_file_content() const override;
    };
}

