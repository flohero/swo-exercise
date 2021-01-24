//
// Created by florian on 14.01.21.
//
#include <iostream>
#include "test_deque.h"

using namespace swo;

int main() {
  test_deque::simple_iterator_test();

  test_deque::equal_test();
  test_deque::not_equal_test();

  test_deque::is_smaller_than_test();
  test_deque::is_not_smaller_than_with_same_sized_deque_test();
  test_deque::is_not_smaller_than_with_one_bigger_element_test();
  test_deque::is_smaller_equal_than_test();

  test_deque::is_bigger_than_test();
  test_deque::is_not_bigger_than_with_same_sized_deque_test();
  test_deque::is_bigger_equal_than_test();


  test_deque::zero_constructor_test();

  test_deque::simple_push_back_test();
  test_deque::push_back_test();
  test_deque::push_front_test();

  test_deque::pop_back_test();
  test_deque::pop_front_test();

  test_deque::index_operator_test();

  test_deque::get_every_second_element_test();
  test_deque::get_last_element_per_iterator_test();

  test_deque::swap_deque_test();
  test_deque::move_constructor_test();

  return EXIT_SUCCESS;
}