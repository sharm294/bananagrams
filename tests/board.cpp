#include "bananagrams/board.hpp"

#include <iostream>

#include "bananagrams/dictionary.hpp"
#include "helpers.hpp"

int main() {
    auto path = bananas::resolvePath("tests/test_words.txt");
    bananas::Dictionary dict(path);

    bananas::Board board(&dict);
    board.playWord("bard");
    board.playWord("car");
    board.playWord("caste");
    board.playWord("basil");
    std::cout << board << std::endl;
}
