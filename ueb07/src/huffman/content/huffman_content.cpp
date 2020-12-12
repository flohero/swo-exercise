//
// Created by florian on 12.12.20.
//

#include <iostream>
#include "huffman_content.h"

namespace huffman {
  void huffman::huffman_content::encode() {
    std::cout << "Hello from " << __func__ << std::endl;
  }

  huffman_content::huffman_content(const std::string &file) :
          content(file) {
    this->token = new coding_token{*this->stream};
  }

  huffman_content::~huffman_content() {
    delete this->token;
  }

  void huffman::huffman_content::decode() {

  }
}
