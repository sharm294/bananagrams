#include "bananagrams/board.hpp"

#include <iostream>

#include "bananagrams/dictionary.hpp"
#include "helpers.hpp"

int main() {
    auto path = bananas::resolvePath("tests/test_words.txt");
    bananas::Dictionary dict(path);

    bananas::Board board(&dict);
    // board.playWord("bard", 0);
    // board.playWord("car", 0);
    // board.playWord("caste", 0);
    // board.playWord("basil", 0);
    std::cout << board << std::endl;
}
