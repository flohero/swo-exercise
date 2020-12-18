//
// Created by florian on 18.12.20.
//

#include <string>
#include "utils.h"

/**
 * Convert a character to a string.
 * If the character is an escaped character like newline or tab, make it printable
 * @param c character to make printable
 * @param padding make all resulting string have the same amount of characters
 * @param enclose enclose the resulting string
 * @returns a string with printable escape characters
 */
std::string utils::escape_char_to_printable(char c, const std::string& padding, const std::string &enclose) {
  std::string str = enclose;
  switch (c) {
    case '\n':
      str += "\\n" + enclose;
      break;
    case '\t':
      str += "\\t" + enclose;
      break;
    case '\r':
      str += "\\r" + enclose;
      break;
    case '\0':
      str += "\\0" + enclose;
      break;
    default:
      str += c + enclose + padding;
  }
  return str;
}
