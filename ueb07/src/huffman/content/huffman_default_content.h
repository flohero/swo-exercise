//
// Created by florian on 12.12.20.
//

#pragma once

#include "huffman_content.h"

/*
 * Extends the huffman_content class, to use a default string value passed to it.
 */
namespace huffman {
  class huffman_default_content : public huffman_content {
    public:
      explicit huffman_default_content(std::string value);
  };
}
