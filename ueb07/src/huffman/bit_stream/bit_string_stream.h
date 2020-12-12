//
// Created by florian on 08.12.20.
//

#pragma once

#include "bit_stream.h"

namespace huffman {
    class bit_string_stream : public bit_stream {
      public:
        explicit bit_string_stream(const std::string& filename);

        ~bit_string_stream() override = default;

        [[nodiscard]] std::string content() const override;
    };
}

