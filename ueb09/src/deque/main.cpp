//
// Created by florian on 14.01.21.
//
#include <iostream>
#include "deque.h"

using namespace swo;

int main() {
  deque<std::string> d{2, "3"};
  //d.push_back("2");
  //d.push_back("4");
  d.push_back("4");
  d.size();
}