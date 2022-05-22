#include "bananagrams/bananagrams.hpp"

#include <algorithm>
#include <iostream>

#include "bananagrams/board.hpp"
#include "helpers.hpp"

int main() {
    auto path = bananas::resolvePath("tests/all_words.txt");

    std::string chars = "AOUEISXAAIKAOEAQRGBRPINAA";
    std::transform(chars.begin(), chars.end(), chars.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    auto board = bananas::play(path, chars);
    std::cout << board << std::endl;
}
