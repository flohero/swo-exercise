//       $Id: deque.h 2709 2021-01-10 11:19:47Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS20/VZ/deque/deque.h $
// $Revision: 2709 $
//     $Date: 2021-01-10 12:19:47 +0100 (So., 10 Jän 2021) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: January 10, 2021
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include "loop_back_counter.h"

#define DEFAULT_SIZE 256
#define MIN_SIZE 0

namespace swo {

  template<typename T>
  class deque final {
  public:
    using const_reference = T const &;
    using reference = T &;
    using size_type = std::size_t;
    using value_type = T;

    /**
     * Two deques are equal when their elements at an index i are equal, their size and capacity must also be equal,
     * first and last do not have to be equal
     * @param lhs
     * @param rhs
     * @returns if lhs and rhs are equal
     * */
    friend bool operator==(deque const &lhs, deque const &rhs) noexcept {
      if (lhs.size_ != rhs.size_ || lhs.capacity != rhs.capacity) {
        return false;
      }
      for (size_type i = 0; i < lhs.size_; i++) {
        if (lhs[i] != rhs[i]) {
          return false;
        }
      }
      return true;
    }

    /**
     * Two deques are not equal if either the size or capacity is not equal, or the elements at an index are not equal
     * @param lhs
     * @param rhs
     * @returns if lhs and rhs are not equal
     * */
    friend bool operator!=(deque const &lhs, deque const &rhs) noexcept {
      return !(lhs == rhs);
    }

    /**
     * @param lhs
     * @param rhs
     * @returns if lhs.size, lhs.capacity and all lhs elements are smaller than its rhs counterparts
     */
    friend bool operator<(deque const &lhs, deque const &rhs) noexcept {
      if (lhs.size_ >= rhs.size_ || lhs.capacity >= rhs.capacity) {
        return false;
      }
      for (size_type i = 0; i < lhs.size_; i++) {
        if (lhs[i] >= rhs[i]) {
          return false;
        }
      }
      return true;
    }

    /**
     * @param lhs
     * @param rhs
     * @returns if one deque is smaller equal to another deque
     */
    friend bool operator<=(deque const &lhs, deque const &rhs) noexcept {
      return lhs < rhs || lhs == rhs;
    }

    friend bool operator>(deque const &lhs, deque const &rhs) noexcept {
      return !(lhs <= rhs);
    }

    friend bool operator>=(deque const &lhs, deque const &rhs) noexcept {
      return lhs > rhs || lhs == rhs;
    }

    friend void swap(deque<T> &a, deque<T> &b) noexcept {
      a.swap(b);
    }

    class iterator final {
    public:
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::random_access_iterator_tag;
      using pointer = T *;
      using reference = T &;
      using value_type = T;

      friend bool operator==(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.index == rhs.index;
      }

      friend bool operator!=(iterator const &lhs, iterator const &rhs) noexcept {
        return !(lhs == rhs);
      }

      friend bool operator<(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.index < rhs.index;
      }

      friend bool operator<=(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.index <= rhs.index;
      }

      friend bool operator>(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.index > rhs.index;
      }

      friend bool operator>=(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.index >= rhs.index;
      }

      // Do not touch
      friend iterator operator+(iterator itor, difference_type offset) noexcept {
        return itor += offset;
      }

      // Do not touch
      friend iterator operator-(iterator itor, difference_type offset) noexcept {
        return itor -= offset;
      }

      iterator() = default;

      iterator(iterator const &src) :
          index{src.index}, deq{src.deq} {}

      ~iterator() = default;

      iterator &operator=(iterator const &src) {
        if(this == src) {
          this->deq = src.deq;
          this->pos = src.pos;
          this->index = src.index;
        }
        return *this;
      }

      reference operator*() {
        return this->deq->at(index);
      }

      pointer operator->() {
        return &this->deq->at(index);
      }

      reference operator[](difference_type offset) {
        return *(*this + offset);
      }

      iterator &operator++() noexcept {
        this->index++;
        return *this;
      }

      iterator operator++(int) noexcept {
        deque<T>::iterator old{*this};
        ++*this;
        return old;
      }

      iterator &operator--() noexcept {
        this->index--;
        return *this;
      }

      iterator operator--(int) noexcept {
        deque<T>::iterator old{*this};
        --*this;
        return old;
      }

      iterator &operator+=(difference_type offset) noexcept {
        this->index += offset;
        return *this;
      }

      iterator &operator-=(difference_type offset) noexcept {
        this->index -= offset;
        return *this;
      }

    private:
      size_type index{0};
      deque<T> *deq{nullptr};

      friend class deque<T>;

      iterator(size_type index, deque *deq) :
          deq{deq}, index{index} {}
    };

    /**
     * Initialize the deque with a default size
     */
    deque() : capacity{DEFAULT_SIZE},
              buffer{new value_type[capacity]},
              last{capacity},
              first{capacity} {}

    /**
     * Initialize the deque with  defined size
     * @param count the maximal amount of elements the deque can hold
     */
    explicit deque(size_type count) : capacity{count},
                                      last{capacity},
                                      first{capacity} {
      // Check if count is bigger than zero, even though size_t can be negative since it is unsigned
      if (count <= MIN_SIZE) {
        throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
      }
      buffer = new value_type[capacity];
    }

    /**
     * Creates a new deque with a specified size and a default element
     * @param count size of deque
     * @param value default element
     */
    deque(size_type count, T const &value) : capacity{count},
                                             last{capacity},
                                             first{capacity} {
      if (count <= MIN_SIZE) {
        throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
      }
      buffer = new value_type[capacity];
      for (size_type i = 0; i < count; i++) {
        push_back(value);
      }
    }

    deque(deque const &src) : capacity{src.capacity},
                              last{src.last},
                              first{src.first} {
      for (auto it: src) {
        this->push_back(it);
      }
    }

    deque(deque &&src) noexcept:
        capacity{src.capacity},
        size_{src.size_},
        last{src.last},
        first{src.first},
        buffer{src.buffer} {
      src.buffer = nullptr;
    }

    deque(std::initializer_list<T> init) : capacity{init.size()},
                                           buffer{new value_type[capacity]},
                                           last{capacity},
                                           first{capacity} {
      for (const auto &it: init) {
        this->push_back(it);
      }
    }

    ~deque() {
      delete[] this->buffer;
    }


    deque &operator=(deque const &src) {
      if(this == src) {
        delete[]this->buffer;
        this->buffer = new value_type[src.capacity];
        this->first = 0;
        size_type count = 0;
        for (auto it : src) {
          this->buffer[count] = it;
          count++;
        }
        this->last = count - 1;
        this->size_ = count;
      }
      return *this;
    }

    deque &operator=(deque &&src) noexcept {
      if (this != *src) {
        this->buffer = src.buffer;
        src.buffer = nullptr;
        this->size_ = src.size_;
        this->first = src.first;
        this->last = src.last;
        this->capacity = src.capacity;
      }
      return *this;
    }

    deque &operator=(std::initializer_list<T> init) {
      delete[]this->buffer;
      this->last = 0;
      this->first = 0;
      this->size_ = 0;
      this->capacity = init.size();
      this->buffer = new value_type[this->capacity];
      for (auto it : init) {
        this->push_back(it);
      }
    }

    const_reference operator[](size_type pos) const {
      return this->at(pos);
    }

    reference operator[](size_type pos) {
      return this->at(pos);
    }

    const_reference at(size_type pos) const {
      if (this->first + pos > this->size()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->first + pos];
    }

    reference at(size_type pos) {
      if (this->first + pos > this->size()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->first + pos];
    }

    const_reference back() const {
      throw_on_empty();
      return this->buffer[this->last()];
    }

    reference back() {
      throw_on_empty();
      return this->buffer[this->last()];
    }

    const_reference front() const {
      throw_on_empty();
      return this->buffer[this->first()];
    }

    reference front() {
      throw_on_empty();
      return this->buffer[this->first()];
    }


    /**
     * @returns the first valid iterator
     */
    iterator begin() noexcept {
      return iterator{0, this};
    }

    /**
     * @returns the last valid iterator + 1
     */
    iterator end() noexcept {
      return iterator{this->size_, this};
    }

    /**
     * Check if the deque is empty.
     * Name is misleading, usually a method checking if the object has a specific characteristic
     * is named "is_<adjective>", not just "<adjective>".
     * The naming of member variables would also not result in conflicts.
     * @returns if the deque is empty
     */
    bool empty() const noexcept {
      return this->size_ == 0;
    }

    /**
     * Count of elements in deque
     * @returns the count of elements in the deque
     */
    size_type size() const noexcept {
      return this->size_;
    }

    void clear() noexcept {
      this->last = 0;
      this->first = 0;
      this->capacity = 0;
      this->size_ = 0;
      delete[]this->buffer;
      this->buffer = nullptr;
    }

    void push_back(T const &value) {
      auto_resize();
      if (this->empty()) {
        this->buffer[this->last()] = value;
      } else {
        this->buffer[++this->last] = value;
      }
      this->size_++;
    }

    void push_back(T &&value) {
      auto_resize();
      if (this->empty()) {
        this->buffer[this->last()] = value;
      } else {
        this->buffer[++this->last] = value;
      }
      this->size_++;
    }

    void pop_back() {
      throw_on_empty();
      if (this->size() != 1) {
        this->last--;
      }
      this->size_--;
    }

    void push_front(T const &value) {
      auto_resize();
      if (this->empty()) {
        this->buffer[this->first()] = value;
      } else {
        this->buffer[--this->first] = value;
      }
      this->size_++;
    }

    void push_front(T &&value) {
      auto_resize();
      if (this->empty()) {
        this->buffer[this->first()] = value;
      } else {
        this->buffer[--this->first] = value;
      }
      this->size_++;
    }

    void pop_front() {
      throw_on_empty();
      if (this->size() != 1) {
        this->first++;
      }
      this->size_--;
    }

    void resize(size_type count) {
      if (count <= this->capacity) {
        throw std::invalid_argument{"New count must be bigger than old count"};
      }
      auto new_buffer = new value_type[count];
      size_type i = 0;
      for (auto it: *this) {
        new_buffer[i] = it;
        i++;
      }
      delete[]this->buffer;
      this->capacity = count;
      this->buffer = new_buffer;
      this->first = loop_back_counter{this->capacity};
      this->last = loop_back_counter{this->capacity, i - 1};
    }

    void resize(size_type count, T const &value) {
      auto old_count = this->capacity;
      this->resize(count);
      for (size_type i = old_count; i < this->capacity; i++) {
        push_back(value);
      }
    }

    void swap(deque &other) noexcept {
      std::swap(this->size_, other.size_);
      std::swap(this->last, other.last);
      std::swap(this->first, other.first);
      std::swap(this->buffer, other.buffer);
      std::swap(this->capacity, other.capacity);
    }

  private:
    size_type capacity;
    size_type size_{0};
    value_type *buffer{nullptr};
    loop_back_counter last;
    loop_back_counter first;

    [[nodiscard]] bool full() const {
      return this->capacity == this->size();
    }

    /**
     * Resizes the buffer automatically if its full
     */
    void auto_resize() {
      if (full()) {
        resize(capacity * 2);
      }
    }

    void throw_on_empty() const {
      if (empty()) {
        throw std::out_of_range{"Deque is empty"};
      }
    }
  };
}