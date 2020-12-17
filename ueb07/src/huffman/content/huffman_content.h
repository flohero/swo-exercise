//
// Created by florian on 12.12.20.
//

#pragma once

#include "content.h"
#include "../coding_token.h"

namespace huffman {
  /**
   * Aka text_coder, but I really didn't like the name.
   * Here is a nice article why classes/objects ending with 'er' are wrong:
   * <link>https://www.yegor256.com/2015/03/09/objects-end-with-er.html</link>
   * Implementation of the huffman encoding and decoding.
   * Extends the content class.
   */
  class huffman_content : public content {
    public:
      huffman_content() = default;

      explicit huffman_content(const std::string &file);

      ~huffman_content();

      [[nodiscard]] std::string encode() const override;

      [[nodiscard]] std::string decode(std::string encoded) const override;

      void statistics() const;

    protected:
      coding_token *token = nullptr;

  };
}

