//
// Created by florian on 12.12.20.
//

#include <iostream>
#include "huffman_content.h"

#define BITS_PER_CHARACTER 8

namespace huffman {
  huffman_content::huffman_content(const std::string &file) :
          content(file) {
    this->token = new coding_token{this->stream->content()};
  }

  huffman_content::~huffman_content() {
    delete this->token;
  }

  std::string huffman_content::encode() const {
    std::string encoded;
    for (char c: this->stream->content()) {
      auto val = this->token->char_to_bitcode(c);
      encoded += val.to_string();
    }
    return encoded;
  }

  std::string huffman_content::decode(std::string encoded) const {
    std::string decoded;
    while(encoded.length() != 0) {
      bool match = false;
      for(const auto& it: this->token->codes()) {
        const std::string &bit_code_str = it.to_string();
        if(encoded.rfind(bit_code_str, 0) == 0) {
          match = true;
          encoded = encoded.substr(bit_code_str.length());
          decoded += it.get_character();
        }
      }
      if(!match) {
        throw std::runtime_error("No matching code was found");
      }
    }
    return decoded;
  }

  void huffman_content::statistics() const {
    std::string codes = encode();
    std::string str = decode(codes);
    if(str != stream->content()) {
      throw std::runtime_error("Error when calculating huffman code");
    }
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
              << std::endl
              << codes << std::endl
              << str;
  }
}
