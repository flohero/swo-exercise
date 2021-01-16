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
        return lhs.pos == rhs.pos;
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

      friend class deque<T>;

      iterator(value_type *pos, deque *deq) :
          pos{pos}, deq{deq} {}
    };

    /**
     * Initialize the deque with a default size
     */
    deque() : deque{DEFAULT_SIZE} {}

    /**
     * Initialize the deque with  defined size
     * @param count the maximal amount of elements the deque can hold
     */
    explicit deque(size_type count) : capacity{count}, head{count}, tail{count} {
      // Check if count is bigger than zero, even though size_t can be negative since it is unsigned
      if (count <= MIN_SIZE) {
        throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
      }
      this->buffer = new T[count];
    }

    /**
     * Creates a new deque with a specified size and a default element
     * @param count size of deque
     * @param value default element
     */
    deque(size_type count, T const &value) : deque{count} {
      for (size_type i = 0; i < count; i++) {
        push_back(value);
      }
    }

    deque(deque const &src) : deque{src.size()} {
      this->head = src.head;
      this->tail = src.tail;
      this->buffer_empty = src.buffer_empty;
      for(auto it: src) {
        this->push_back(it);
      }
    }

    deque(deque &&src) noexcept;

    deque(std::initializer_list<T> init) : deque{init.size()} {
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

    const_reference operator[](size_type pos) const;

    reference operator[](size_type pos);

    const_reference at(size_type pos) const;

    reference at(size_type pos);

    const_reference back() const;

    reference back();

    const_reference front() const;

    reference front();
    */
    iterator begin() noexcept {
      return iterator{this->buffer + this->head(), this};
    }

    iterator end() noexcept {
      return iterator{this->buffer + this->tail() + 1, this};
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
      if (this->empty()) {
        return 0;
      }
      auto start = const_cast<swo::deque<value_type> *>(this)->begin();
      auto end = const_cast<swo::deque<value_type> *>(this)->end();
      size_type count = 0;
      for (auto it = start; it != end; it++, count++);
      return count;
    }

    void clear() noexcept {
      this->head = 0;
      this->head = 0;
      this->buffer_empty = true;
    }

    void push_back(T const &value) {
      // TODO fix push back
      if (this->empty()) {
        this->buffer_empty = false;
        this->buffer[this->tail()] = value;
      } else {
        this->buffer[--this->tail] = value;
      }
    }

    void push_back(T &&value) {
      if (this->full()) {
        throw std::overflow_error{"Deque is fulL"};
      }
      if (this->empty()) {
        this->buffer_empty = false;
        this->buffer[this->tail()] = value;
      } else {
        this->buffer[--this->tail] = value;
      }
    }

    /*
    void pop_back();

    void push_front(T const &value);

    void push_front(T &&value);

    void pop_front();

    void resize(size_type count);

    void resize(size_type count, T const &value);

    void swap(deque &other) noexcept;
    */
  private:
    value_type *buffer{nullptr};
    size_type capacity;
    loop_back_counter head;
    loop_back_counter tail;
    bool buffer_empty{true};

    bool full() const {
      return !this->buffer_empty && this->head == this->tail;
    }

  };
}