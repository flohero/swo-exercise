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

namespace swo {

  template<typename T>
  class deque final {
  public:
    using const_reference = T const &;
    using reference = T &;
    using size_type = std::size_t;
    using value_type = T;

    friend bool operator==(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator!=(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator<(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator<=(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator>(deque const &lhs, deque const &rhs) noexcept;

    friend bool operator>=(deque const &lhs, deque const &rhs) noexcept;

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

      friend bool operator==(iterator const &lhs, iterator const &rhs) noexcept;

      friend bool operator!=(iterator const &lhs, iterator const &rhs) noexcept;

      friend bool operator<(iterator const &lhs, iterator const &rhs) noexcept;

      friend bool operator<=(iterator const &lhs, iterator const &rhs) noexcept;

      friend bool operator>(iterator const &lhs, iterator const &rhs) noexcept;

      friend bool operator>=(iterator const &lhs, iterator const &rhs) noexcept;

      friend iterator operator+(iterator itor, difference_type offset) noexcept {
        return itor += offset;
      }

      friend iterator operator-(iterator itor, difference_type offset) noexcept {
        return itor -= offset;
      }

      iterator();

      iterator(iterator const &src);

      ~iterator();

      iterator &operator=(iterator const &src);

      reference operator*();

      pointer operator->();

      reference operator[](difference_type offset);

      iterator &operator++() noexcept;

      iterator operator++(int) noexcept;

      iterator &operator--() noexcept;

      iterator operator--(int) noexcept;

      iterator &operator+=(difference_type offset) noexcept;

      iterator &operator-=(difference_type offset) noexcept;
    };

    deque();

    explicit deque(size_type count);

    deque(size_type count, T const &value);

    deque(deque const &src);

    deque(deque &&src) noexcept;

    deque(std::initializer_list<T> init);

    ~deque();

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

    iterator begin() noexcept;

    iterator end() noexcept;

    bool empty() const noexcept;

    size_type size() const noexcept;

    void clear() noexcept;

    void push_back(T const &value);

    void push_back(T &&value);

    void pop_back();

    void push_front(T const &value);

    void push_front(T &&value);

    void pop_front();

    void resize(size_type count);

    void resize(size_type count, T const &value);

    void swap(deque &other) noexcept;

  private:
    value_type *buffer{nullptr};
    int head{0};
    int tail{0};
    bool buffer_empty{false};

  };
}   // namespace swo
