//
// Created by florian on 12.12.20.
//

#include <iostream>
#include "huffman_content.h"

#define BITS_PER_CHARACTER 8

namespace huffman {
  huffman_content::huffman_content(const std::string &file) :
          content(file) {
    this->token = new coding_token{*this->stream};
  }

  huffman_content::~huffman_content() {
    delete this->token;
  }

  std::string huffman_content::encode() {
    std::string encoded;
    auto coding_map = this->token->coding_map();
    for (char c: this->stream->content()) {
      auto val = coding_map->find(c);
      encoded += val->second.to_string();
    }
    delete coding_map;
    statistics(encoded);
    return encoded;
  }

  std::string huffman_content::decode(std::string encoded) {

    return "";
  }

  void huffman_content::statistics(const std::string &codes) const {
    this->token->print();
    std::cout << std::endl;
    auto code_size = static_cast<double>(codes.length());
    auto input_size = static_cast<double>(this->stream->content().length() * BITS_PER_CHARACTER);
    auto compression_rate = static_cast<double>(code_size / input_size * 100);
    std::cout << "Encoding stats:" << std::endl
              << "-------------------" << std::endl
              << "Original Size    : " << input_size        << " bits" << std::endl
              << "Size Now         : " << code_size         << " bits" << std::endl
              << "Compression Rate : " << compression_rate  << "%"     << std::endl
              << std::endl;
  }
}
