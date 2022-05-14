#include "bananagrams/board.hpp"

#include <iostream>

#include "bananagrams/graph.hpp"
#include "helpers.hpp"

int main() {
    auto path = bananas::resolvePath("tests/test_words.txt");
    bananas::Graph graph(path);

    bananas::Board board(&graph);
    board.playWord("bard");
    board.playWord("car");
    board.playWord("caste");
    board.playWord("basil");
    std::cout << board << std::endl;
}
