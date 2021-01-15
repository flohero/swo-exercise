//
// Created by florian on 14.01.21.
//
#include <iostream>
#include "deque.h"

using namespace swo;

int main() {
  deque<int> d{10, 4};
  d.push_back(10);
  auto it = d.begin();
  auto it2 = it + 1;
  d.size();
}