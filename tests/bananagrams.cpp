#include "bananagrams/bananagrams.hpp"

#include <algorithm>
#include <iostream>

#include "bananagrams/board.hpp"
#include "bananagrams/dictionary.hpp"
#include "helpers.hpp"

int main() {
    auto path = bananas::resolvePath("tests/test_words.txt");

    std::string chars = "bardcaasteasil";
    std::transform(chars.begin(), chars.end(), chars.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    bananas::DictionaryFindOptions options;
    auto board = bananas::play(path, options, chars);
    std::cout << board << std::endl;
}
