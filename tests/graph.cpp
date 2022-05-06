#include "bananagrams/graph.hpp"

#include <iostream>

#include "helpers.hpp"

namespace bananas {

void printTest0() {
    auto path = resolvePath("tests/test_words.txt");
    auto root = initializeGraph(path);
    GraphPrintOptions options;
    options.depth = -1;
    options.style = GraphPrintOptions::Style::kList;
    printGraph(root.get(), options);
}

}  // namespace bananas

int main() {
    bananas::printTest0();
    return 0;
}
