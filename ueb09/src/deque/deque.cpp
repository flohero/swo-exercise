//
// Created by florian on 14.01.21.
//

#include "deque.h"

#define DEFAULT_SIZE 256
#define MIN_SIZE 0

namespace swo {
  /* Constructors */

  /**
   * Initialize the deque with  defined size
   * @param count the maximal amount of elements the deque can hold
   */
  template<typename T>
  deque<T>::deque(deque::size_type count) {
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
    this->buffer_empty = false;
    // TODO insert value as default element
  }

  /**
   * Destruct deque
   */
  template<typename T>
  deque<T>::~deque<T>() {
    delete[] this->buffer;
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
}