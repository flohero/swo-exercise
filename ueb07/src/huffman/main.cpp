#include <iostream>
#include "content/huffman_default_content.h"

using namespace huffman;

void test() {
  std::string separator = " *** ";

  // Standard Test Case
  std::cout << separator
            << "Standard Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_default_content{
          "AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC"
  }.statistics();

  // Read from an existing file
  /*
   Content of file is:
   AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC
   */

  std::cout << std::endl << std::endl << separator
            << "Read From Existing File Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_content{
          "../resources/test.txt"
  }.statistics();

  // Read from an non existing file
  std::cout << std::endl << std::endl << separator
            << "Read From Non Existing File Test Case"
            << separator << std::endl
            << "Expecting a run_time exception" << std::endl;
  try {
    huffman_content{
            "./path/to/non/existing.file"
    }.statistics();
  } catch (std::runtime_error &err) {
    std::cout << "Caught Runtime Exception!" << std::endl
              << err.what() << std::endl;
  }

  // Read from an empty file
  std::cout << std::endl << std::endl << separator
            << "Read From Empty File Test Case"
            << separator << std::endl
            << "Expecting a invalid_argument exception" << std::endl;
  try {
    huffman_content{
            "../resources/empty.txt"
    }.statistics();
  } catch (std::invalid_argument &err) {
    std::cout << "Caught Invalid Argument Exception!" << std::endl
              << err.what() << std::endl;
  }

   // Empty Content Test Case
  std::cout << std::endl << std::endl << separator
            << "Empty Content Test Case"
            << separator << std::endl
            << "Expecting a invalid_argument exception" << std::endl;
  try {
    huffman_default_content{
            ""
    }.statistics();
  } catch (std::invalid_argument &err) {
    std::cout << "Caught Invalid Argument Exception!" << std::endl
              << err.what() << std::endl;
  }

  // Single Character Test Case
  std::cout << std::endl << std::endl << separator
            << "Single Character Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_default_content{
          "a"
  }.statistics();

  // Four unique Characters Test Case
  std::cout << std::endl << std::endl << separator
            << "Four unique Characters Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_default_content{
          "asdf"
  }.statistics();

  // Simple Test Case
  std::cout << std::endl << std::endl << separator
            << "Simple Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_default_content{
          "aabbcc"
          }.statistics();

  // 200 Word Test Case
  std::cout << std::endl << std::endl << separator
            << "200 Word Test Case"
            << separator << std::endl
            << "Expecting a successful run" << std::endl;
  huffman_content{
          "../resources/lorem.txt"
  }.statistics();
}

int main() {
  test();
  return EXIT_SUCCESS;
}
