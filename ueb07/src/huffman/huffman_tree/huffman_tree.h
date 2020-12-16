//
// Created by florian on 14.12.20.
//

#pragma once

#include "../frequencies/frequency_table.h"

namespace huffman {
  class huffman_tree {
    public:
      explicit huffman_tree(const frequency_table &freq_table);

      ~huffman_tree();

      [[nodiscard]] huffman_tree_node *get_root() const;

      void print() const;

    private:
      huffman_tree_node *root;

  };
}
