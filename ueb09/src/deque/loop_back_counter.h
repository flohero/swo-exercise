//
// Created by florian on 14.01.21.
//

#pragma once

namespace swo {

  /**
   * Implement a counter which automatically loops back to zero if a specified value is reached
   * or if a value smaller than zero is reached
   */
  class loop_back_counter {
  public:
    using size_type = std::size_t;

    explicit loop_back_counter(size_type limit) : limit{limit} {}

    loop_back_counter(size_type limit, size_type counter) : counter{counter}, limit{limit} {}

    /**
     * Prefix ++ operator. Increments first and then returns updated value
     * @return updated value
     */
    size_type operator++() {
      counter++;
      if (counter == limit) {
        counter = 0;
      }
      return counter;
    }

    /**
     * Postfix ++ operator. Returns old value and then increments
     * @return old value
     */
    size_type operator++(int) {
      size_type old = this->counter;
      ++*this;
      return old;
    }

    /**
     * Prefix -- operator. Decrements first and then returns updated value
     * @return updated value
     */
    size_type operator--() {
      if (counter == 0) {
        counter = limit;
      }
      return --counter;
    }

    /**
     * Postfix -- operator. Returns old value and then decrements
     * @return old value
     */
    size_type operator--(int) {
      size_type old = this->counter;
      --*this;
      return old;
    }

    /**
     * @return counter value
     */
    size_type operator()() const {
      return counter;
    }

    size_type operator+(const size_type add) const {
      return ((counter + add) % limit);
    }

    loop_back_counter &operator=(size_type new_val) {
      this->counter = new_val % limit;
      return *this;
    }

    bool operator==(const loop_back_counter &other) const {
      return other.counter == this->counter && other.limit == this->limit;
    }

  private:
    size_type counter{0};
    size_type limit;
  };
}

