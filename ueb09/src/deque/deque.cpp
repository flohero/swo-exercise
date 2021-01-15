//
// Created by florian on 14.01.21.
//
#include "deque.h"

#define DEFAULT_SIZE 256
#define MIN_SIZE 0

namespace swo {
  /*   ITERATOR   */
  /*   Friends    */
  template<typename T>
  bool operator==(typename deque<T>::iterator const &lhs,
                  typename deque<T>::iterator const &rhs) noexcept {
    return lhs.pos == rhs.pos && lhs.deq == rhs.deq;
  }

  template<typename T>
  bool operator!=(typename deque<T>::iterator const &lhs,
                  typename deque<T>::iterator const &rhs) noexcept {
    return !(*lhs == rhs);
  }

  /* Constructors */
  template<typename T>
  deque<T>::iterator::iterator() = default;

  template<typename T>
  deque<T>::iterator::iterator(const iterator &src):
      pos{src.pos}, deq{src.deq} {}

  template<typename T>
  deque<T>::iterator::iterator(value_type *pos, deque<T> *deq):
      pos{pos}, deq{deq} {}

  template<typename T>
  deque<T>::iterator::~iterator() = default;

  /* Methods */
  template<typename T>
  typename deque<T>::iterator &deque<T>::iterator::operator=(const iterator &src) {
    this->deq = src.deq;
    this->pos = src.pos;
    return *this;
  }

  template<typename T>
  typename deque<T>::iterator::reference deque<T>::iterator::operator*() {
    return *this->pos;
  }

  template<typename T>
  typename deque<T>::iterator::pointer deque<T>::iterator::operator->() {
    return this->pos;
  }

  template<typename T>
  typename deque<T>::iterator::reference
  deque<T>::iterator::operator[](typename deque<T>::iterator::difference_type offset) {
    return *(*this + offset);
  }

  template<typename T>
  typename deque<T>::iterator &deque<T>::iterator::operator++() noexcept {
    if (this->pos + 1 < this->deq->buffer + this->deq->capacity) {
      this->pos++;
    } else {
      this->pos = this->deq->buffer;
    }
    return *this;
  }

  template<typename T>
  typename deque<T>::iterator deque<T>::iterator::operator++(int) noexcept {
    deque<T>::iterator old{*this};
    ++*this;
    return old;
  }

  template<typename T>
  typename deque<T>::iterator &deque<T>::iterator::operator--() noexcept {
    if (this->pos == deq->buffer) {
      this->pos = this->deq->buffer + this->deq->capacity - 1;
    } else {
      this->pos--;
    }
    return *this;
  }

  template<typename T>
  typename deque<T>::iterator deque<T>::iterator::operator--(int) noexcept {
    deque<T>::iterator old{*this};
    --*this;
    return old;
  }

  template<typename T>
  typename deque<T>::iterator &
  deque<T>::iterator::operator+=(typename deque<T>::iterator::difference_type offset) noexcept {
    if (this->pos + offset < this->deq->buffer + this->deq->capacity) {
      this->pos += offset;
    } else {
      int diff = (this->pos + (offset % this->deq->capacity)) - (this->deq->buffer + this->deq->capacity);
      this->pos = this->deq->buffer + diff;
    }
    return *this;
  }

  template<typename T>
  typename deque<T>::iterator &
  deque<T>::iterator::operator-=(typename deque<T>::iterator::difference_type offset) noexcept {
    if (this->pos - offset >= this->deq->buffer) {
      this->pos -= offset;
    } else {
      int diff = this->deq->buffer - (this->pos - (offset % this->deq->capacity));
      this->pos = (this->deq->buffer + this->deq->capacity) - diff;
    }
    return *this;
  }

  /*    DEQUE     */
  /* Constructors */

  /**
   * Initialize the deque with  defined size
   * @param count the maximal amount of elements the deque can hold
   */
  template<typename T>
  deque<T>::deque(size_type count): capacity{count}, head{capacity}, tail{capacity} {
    // Check if count is bigger than zero, even though size_t can be negative since it is unsigned
    if (count <= MIN_SIZE) {
      throw std::invalid_argument("Count must be bigger than " + std::to_string(MIN_SIZE));
    }
    this->buffer = new T[count];
  }

  /**
   * Initialize the deque with a default size
   */
  template<typename T>
  deque<T>::deque(): deque{DEFAULT_SIZE} {}

  /**
   * Creates a new deque with a specified size and a default element
   * @param count size of deque
   * @param value default element
   */
  template<typename T>
  deque<T>::deque(size_type count, T const &value) : deque{count} {
    for (size_type i = 0; i < count; i++) {
      push_back(value);
    }
  }

  /**
   * Destruct deque
   */
  template<typename T>
  deque<T>::~deque<T>() {
    delete[] this->buffer;
  }

  template<typename T>
  typename deque<T>::iterator deque<T>::begin() noexcept {
    return iterator{this->buffer + this->head(), this};
  }

  template<typename T>
  typename deque<T>::iterator deque<T>::end() noexcept {
    return iterator{this->buffer + this->tail() + 1, this};
  }

  /**
   * Check if the deque is empty.
   * Name is misleading, usually a method checking if the object has a specific characteristic
   * is named "is_<adjective>", not just "<adjective>".
   * The naming of member variables would also not result in conflicts.
   * @returns if the deque is empty
   */
  template<typename T>
  bool deque<T>::empty() const noexcept {
    return this->buffer_empty;
  }

  template<typename T>
  typename deque<T>::size_type deque<T>::size() const noexcept {
    // TODO implement
    return 0;
  }

  template<typename T>
  void deque<T>::clear() noexcept {
    this->head = 0;
    this->head = 0;
    this->buffer_empty = true;
  }

  template<typename T>
  void deque<T>::push_back(const T &value) {
    if (this->empty()) {
      this->buffer_empty = false;
      this->buffer[this->tail()] = value;
    } else {
      this->buffer[--this->tail] = value;
    }
  }

  template<typename T>
  void deque<T>::push_back(T &&value) {
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

  template<typename T>
  bool deque<T>::full() const {
    return !this->buffer_empty && this->head == this->tail;
  }

  template
  class deque<std::string>;

  template
  class deque<int>;
}
