//
// Created by florian on 09.12.20.
//

#include "char_frequency.h"

namespace huffman {
  int char_frequency::count = 0;

  char_frequency::char_frequency() {
    this->total = 0;
    this->frequency = 0;
    this->character = '\0';
  }

  char_frequency::char_frequency(const char character, const int frequency, const size_t total) {
    this->total = total;
    this->character = character;
    this->frequency = frequency;
  }

  /**
   * Combines two char_frequencies to one char_frequency:
   * {id=0, character='a', frequency=10} + {id=1, character='b', frequency=3} = {id=2, character=Nullterminator,  frequency=13}
   * @param freq
   * @returns the resulting char_frequency
   */
  char_frequency char_frequency::operator+(const char_frequency &freq) const {
    char_frequency new_freq{
            this->character == freq.character
            ? this->character : '\0',
            this->frequency + freq.frequency,
            this->total
    };
    return new_freq;
  }

  /**
   * Checks if this char_frequency is smaller than the other.
   * Its smaller if this frequency is smaller than the others.
   * If its the same it checks if the character code is smaller.
   * If both the frequency and character code are the same, the id will be used.
   * @param freq
   * @returns if this char_frequency is smaller
   */
  bool char_frequency::operator<(const char_frequency &freq) const {
    return this->frequency != freq.frequency
           ? this->frequency < freq.frequency
           : (this->character != freq.character
              ? this->character < freq.character
              // If the nodes are identical, just compare the ids.
              : this->id < freq.id);
  }

  /**
   * Same as the smaller Operator, but for bigger.
   * @param freq
   * @returns if this char_frequency is bigger
   */
  bool char_frequency::operator>(const char_frequency &freq) const {
    return !(*this < freq);
  }

  char char_frequency::get_character() const {
    return this->character;
  }

  int char_frequency::get_frequency() const {
    return this->frequency;
  }
}