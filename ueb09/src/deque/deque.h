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
        this->deq = src.deq;
        this->pos = src.pos;
        this->index = src.index;
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
      deque *deq{nullptr};
      size_type index;

      friend class deque<T>;

      iterator(size_type index, deque *deq) :
          deq{deq}, index{index} {}
    };

    /**
     * Initialize the deque with a default size
     */
    deque() : capacity{DEFAULT_SIZE},
              buffer{new T[capacity]},
              last{capacity},
              first{capacity} {}

    /**
     * Initialize the deque with  defined size
     * @param count the maximal amount of elements the deque can hold
     */
    explicit deque(size_type count) : capacity{count},
                                      buffer{new T[capacity]},
                                      last{capacity},
                                      first{capacity} {
      // Check if count is bigger than zero, even though size_t can be negative since it is unsigned
      if (count <= MIN_SIZE) {
        throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
      }
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
      buffer = new T[capacity];
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
                                           buffer{new T[capacity]},
                                           last{capacity},
                                           first{capacity} {
      for (const auto &it: init) {
        this->push_back(it);
      }
    }

    ~deque() {
      delete[] this->buffer;
    }

    /*
    deque &operator=(deque const &src);

    deque &operator=(deque &&src) noexcept;

    deque &operator=(std::initializer_list<T> init);
    */
    const_reference operator[](size_type pos) const {
      return this->at(pos);
    }

    reference operator[](size_type pos) {
      return this->at(pos);
    }

    const_reference at(size_type pos) const {
      if (this->first + pos > this->last()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->first + pos];
    }

    reference at(size_type pos) {
      if (this->first + pos > this->last()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->first + pos];
    }
    /*
    const_reference back() const;

    reference back();

    const_reference front() const;

    reference front();
    */

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
      this->last = 0;
    }

    void push_back(T const &value) {
      if (this->full()) {
        this->resize(this->capacity * 2);
      }
      if (this->empty()) {
        this->buffer[this->last()] = value;
      } else {
        this->buffer[++this->last] = value;
      }
      this->size_++;
    }

    void push_back(T &&value) {
      if (this->full()) {
        this->resize(this->capacity * 2);
      }
      if (this->empty()) {
        this->buffer[this->last()] = value;
      } else {
        this->buffer[++this->last] = value;
      }
      this->size_++;
    }

    /*
    void pop_back();

    void push_front(T const &value);

    void push_front(T &&value);

    void pop_front();
    */
    void resize(size_type count) {
      if (count <= this->capacity) {
        throw std::invalid_argument{"New count must be bigger than old count"};
      }
      auto new_buffer = new T[count];
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
    /*
    void swap(deque &other) noexcept;
    */
  private:
    size_type capacity;
    size_type size_{0};
    value_type *buffer{nullptr};
    loop_back_counter last;
    loop_back_counter first;

    bool full() const {
      return this->capacity == this->size();
    }
  };
}