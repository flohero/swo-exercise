//
// Created by florian on 24.01.21.
//

#pragma once

#include <sstream>
#include <cassert>
#include "deque.h"

#define FUNC std::cout << __func__ << std::endl
namespace swo {
  std::ostream &operator<<(std::ostream &os, deque<std::string> &deq) {
    os << "{";
    if (!deq.empty()) {
      for (deque<std::string>::iterator it = deq.begin(); it < deq.end(); it++) {
        os << "'" << *it << "'" << (it + 1 >= deq.end() ? "" : ", ");
      }
    }
    return os << "}";
  }

  class test_deque {
  public:
    static void simple_print_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{"Hello", " ", "World", "!"};
      std::stringstream ss;
      const char *const exp = "{'Hello', ' ', 'World', '!'}";

      // When
      ss << d;

      // Then
      assert(ss.str() == exp);
      success();
    }

    static void equal_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{10, "TEST"};
      deque<std::string> d2{10, "TEST"};

      // When
      // Then
      assert(d == d2);
      success();
    }

    static void not_equal_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{"Hello", "World", "!"};
      deque<std::string> d2{"Hello", "Flo"};

      // When
      // Then
      assert(d != d2);
      success();
    }

    static void is_smaller_than_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 4};
      deque<int> d2{5, 6, 7, 8, 9};

      // When
      // Then
      assert(d < d2);
      success();
    }

    static void is_not_smaller_than_with_same_sized_deque_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 4};
      deque<int> d2{1, 2, 3, 4};

      // When
      // Then
      assert(!(d < d2));
      success();
    }

    static void is_not_smaller_than_with_one_bigger_element_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 10};
      deque<int> d2{5, 6, 7, 8, 9};

      // When
      // Then
      assert(!(d < d2));
      success();
    }

    static void is_smaller_equal_than_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 10};
      deque<int> d2{1, 2, 3, 10};

      // When
      // Then
      assert(d <= d2);
      success();
    }

    static void is_bigger_than_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 4};
      deque<int> d2{5, 6, 7, 8, 9};

      // When
      // Then
      assert(d2 > d);
      success();
    }

    static void is_not_bigger_than_with_same_sized_deque_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 4};
      deque<int> d2{1, 2, 3, 4};

      // When
      // Then
      assert(!(d > d2));
      success();
    }

    static void is_bigger_equal_than_test() {
      separator();
      FUNC;
      // Given
      deque<int> d{1, 2, 3, 10};
      deque<int> d2{1, 2, 3, 10};

      // When
      // Then
      assert(d >= d2);
      success();
    }


    static void zero_constructor_test() {
      separator();
      FUNC;
      // Given
      bool failed = false;
      bool expected = true;

      // When
      try {
        deque<std::string> d(0);
      } catch (std::invalid_argument &) {
        failed = true;
      }

      // Then
      assert(failed == expected);
      success();
    }

    static void simple_push_back_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{1};
      const std::string val = "Hello";
      deque<std::string> exp{val};

      // When
      d.push_back(val);

      // Then
      assert(d == exp);
      success();
    }

    static void push_back_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{3};
      deque<std::string> exp{"Hello", "World", "!"};

      // When
      d.push_back("Hello");
      d.push_back("World");
      d.push_back("!");

      // Then
      assert(d == exp);
      success();
    }

    static void pop_back_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{"Hello", "World", "!"};
      deque<std::string> exp{3};
      exp.push_back("Hello");
      exp.push_back("World");

      // When
      d.pop_back();

      // Then
      assert(d == exp);
      success();
    }

    static void push_front_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{3};
      deque<std::string> exp{"Hello", "World", "!"};

      // When
      d.push_front("!");
      d.push_front("World");
      d.push_front("Hello");

      // Then
      assert(d == exp);
      success();
    }

    static void pop_front_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{"Hello", "World", "!"};
      deque<std::string> exp{3};
      exp.push_back("World");
      exp.push_back("!");

      // When
      d.pop_front();

      // Then
      assert(d == exp);
      success();
    }

    static void index_operator_test() {
      separator();
      FUNC;
      // Given
      deque<std::string> d{"Hello", "World", "!"};
      std::string exp = "World";

      // When
      std::string res = d[1];

      // Then
      assert(res == exp);
      success();
    }

  private:
    static void separator() {
      std::cout << "--------------------------------------------" << std::endl;
    }

    static void success() {
      std::cout << "SUCCESS!" << std::endl;
    }
  };
}

