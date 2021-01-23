//
// Created by florian on 14.01.21.
//
#include <iostream>
#include "deque.h"

using namespace swo;

int main() {
  deque<std::string> d{1, "3"};
  d.push_back("4");
  d.push_front("3");
  for(auto & it : d) {
    std::cout << it << " ";
  }
  std::cout << std::endl;

  deque<std::string> d2{1};
  d2.push_back("3");
  d2.push_back("3");
  d2.push_back("4");

  if(d == d2) {
    std::cout << "Are equal" << std::endl;
  }

  d2.push_back("4");
  if(d != d2) {
    std::cout << "Are not equal" << std::endl;
  }
}