//
// Created by florian on 12.12.20.
//

#include <iostream>
#include "huffman_content.h"
#include "../bit_code.h"

namespace huffman {
  huffman_content::huffman_content(const std::string &file) :
          content(file) {
    this->token = new coding_token{*this->stream};
  }

  huffman_content::~huffman_content() {
    delete this->token;
  }

  void huffman::huffman_content::encode() {
    this->statistics();
    auto coding_map = this->token->coding_map();
    for (char c: this->stream->content()) {
      auto val = coding_map->find(c);
      bit_code{val->second}.print();
    }
    delete coding_map;
  }

  void huffman::huffman_content::decode() {

  }

  void huffman_content::statistics() const {
    this->token->print();
    std::cout << std::endl;
  }
}
