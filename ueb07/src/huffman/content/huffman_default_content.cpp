//
// Created by florian on 12.12.20.
//

#include "huffman_default_content.h"

#include <utility>
#include "../bit_stream/default_stream.h"

namespace huffman {
  huffman_default_content::huffman_default_content(std::string value){
    this->stream = new default_stream{std::move(value)};
    this->token = new coding_token{*stream};
  }
}
