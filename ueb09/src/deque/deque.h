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

    /*
    friend bool operator==(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator!=(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator<(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator<=(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator>(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator>=(deque const &lhs, deque const &rhs) noexcept;
    */
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
        return lhs.pos == rhs.pos && lhs.iterate_count == rhs.iterate_count;
      }

      friend bool operator!=(iterator const &lhs, iterator const &rhs) noexcept {
        return !(lhs == rhs);
      }

      friend bool operator<(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.pos < rhs.pos;
      }

      friend bool operator<=(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.pos <= rhs.pos;
      }

      friend bool operator>(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.pos > rhs.pos;
      }

      friend bool operator>=(iterator const &lhs, iterator const &rhs) noexcept {
        return lhs.pos >= rhs.pos;
      }

      friend iterator operator+(iterator itor, difference_type offset) noexcept {
        return itor += offset;
      }

      friend iterator operator-(iterator itor, difference_type offset) noexcept {
        return itor -= offset;
      }

      iterator() = default;

      iterator(iterator const &src) :
          pos{src.pos}, deq{src.deq} {}

      ~iterator() = default;

      iterator &operator=(iterator const &src) {
        this->deq = src.deq;
        this->pos = src.pos;
        return *this;
      }

      reference operator*() {
        return *this->pos;
      }

      pointer operator->() {
        return this->pos;
      }

      reference operator[](difference_type offset) {
        return *(*this + offset);
      }

      iterator &operator++() noexcept {
        if (this->pos + 1 < this->deq->buffer + this->deq->capacity) {
          this->pos++;
        } else {
          this->pos = this->deq->buffer;
        }
        iterate_count++;
        return *this;
      }

      iterator operator++(int) noexcept {
        deque<T>::iterator old{*this};
        ++*this;
        return old;
      }

      iterator &operator--() noexcept {
        if (this->pos == deq->buffer) {
          this->pos = this->deq->buffer + this->deq->capacity - 1;
        } else {
          this->pos--;
        }
        return *this;
      }

      iterator operator--(int) noexcept {
        deque<T>::iterator old{*this};
        --*this;
        return old;
      }

      iterator &operator+=(difference_type offset) noexcept {
        if (this->pos + offset < this->deq->buffer + this->deq->capacity) {
          this->pos += offset;
        } else {
          size_type diff = (this->pos + (offset % this->deq->capacity)) - (this->deq->buffer + this->deq->capacity);
          this->pos = this->deq->buffer + diff;
        }
        return *this;
      }

      iterator &operator-=(difference_type offset) noexcept {
        if (this->pos - offset >= this->deq->buffer) {
          this->pos -= offset;
        } else {
          size_type diff = this->deq->buffer - (this->pos - (offset % this->deq->capacity));
          this->pos = (this->deq->buffer + this->deq->capacity) - diff;
        }
        return *this;
      }

    private:
      value_type *pos{nullptr};
      deque *deq{nullptr};
      size_type iterate_count{0}; // count how often the iterator has been incremented
      //size_type index;

      friend class deque<T>;

      iterator(value_type *pos, deque *deq) :
          pos{pos}, deq{deq} {}

      iterator(value_type *pos, deque *deq, size_type iterate_count) :
          pos{pos}, deq{deq}, iterate_count{iterate_count} {}
    };

    /**
     * Initialize the deque with a default size
     */
    deque() : capacity{DEFAULT_SIZE},
              buffer{new T[capacity]},
              head{capacity},
              tail{capacity} {}

    /**
     * Initialize the deque with  defined size
     * @param count the maximal amount of elements the deque can hold
     */
    explicit deque(size_type count) : capacity{count},
                                      buffer{new T[capacity]},
                                      head{capacity},
                                      tail{capacity} {
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
                                             head{capacity},
                                             tail{capacity} {
      if (count <= MIN_SIZE) {
        throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
      }
      buffer = new T[capacity];
      for (size_type i = 0; i < count; i++) {
        push_back(value);
      }
    }

    deque(deque const &src) : capacity{src.capacity},
                              head{src.head},
                              tail{src.tail},
                              buffer_empty{src.buffer_empty} {
      for (auto it: src) {
        this->push_back(it);
      }
    }

    deque(deque &&src) noexcept;

    deque(std::initializer_list<T> init) : capacity{init.size()},
                                           buffer{new T[capacity]},
                                           head{capacity},
                                           tail{capacity} {
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
      if(this->tail + pos > this->head()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->tail + pos];
    }

    reference operator[](size_type pos) {
      if(this->tail + pos > this->head()) {
        throw std::out_of_range{"Index out of bounds"};
      }
      return this->buffer[this->tail + pos];
    }
    /*
    const_reference at(size_type pos) const;

    reference at(size_type pos);

    const_reference back() const;

    reference back();

    const_reference front() const;

    reference front();
    */
    iterator begin() noexcept {
      return iterator{this->buffer + this->tail(), this};
    }

    iterator end() noexcept {
      value_type *pos = this->buffer + (this->head + 1);
      return iterator{pos, this, this->size_};
    }

    /**
     * Check if the deque is empty.
     * Name is misleading, usually a method checking if the object has a specific characteristic
     * is named "is_<adjective>", not just "<adjective>".
     * The naming of member variables would also not result in conflicts.
     * @returns if the deque is empty
     */
    bool empty() const noexcept {
      return this->buffer_empty;
    }

    size_type size() const noexcept {
      return this->size_;
    }

    void clear() noexcept {
      this->head = 0;
      this->head = 0;
      this->buffer_empty = true;
    }

    void push_back(T const &value) {
      if (this->full()) {
        this->resize(this->capacity * 2);
      }
      if (this->empty()) {
        this->buffer_empty = false;
        this->buffer[this->head()] = value;
      } else {
        this->buffer[++this->head] = value;
      }
      this->size_++;
    }

    void push_back(T &&value) {
      if (this->full()) {
        this->resize(this->capacity * 2);
      }
      if (this->empty()) {
        this->buffer_empty = false;
        this->buffer[this->head()] = value;
      } else {
        this->buffer[++this->head] = value;
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
      const iterator &anEnd = this->end();
      const iterator &start = this->begin();
      for (auto it: *this) {
        new_buffer[i] = it;
        i++;
      }
      delete[]this->buffer;
      this->capacity = count;
      this->buffer = new_buffer;
      this->tail = loop_back_counter{this->capacity};
      this->head = loop_back_counter{this->capacity, i - 1};
    }

    void resize(size_type count, T const &value) {
      auto old_count = this->capacity;
      this->resize(count);
      for(size_type i = old_count; i < this->capacity; i++) {
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
    loop_back_counter head;
    loop_back_counter tail;
    bool buffer_empty{true};

    bool full() const {
      return this->capacity == this->size();
    }
  };
}