#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.hpp"

namespace bananas {

class CharMap;

struct GraphPrintOptions {
    enum Style { kTree, kList };

    // global options
    Style style = Style::kTree;
    std::ostream& stream = std::cout;

    // kTree options
    int depth = -1;
};

class Graph {
   public:
    explicit Graph(const std::string& path_to_words_file);

    bool isWord(const std::string& word);
    std::vector<std::string> findWords(CharMap characters);

    void print(const GraphPrintOptions& options = GraphPrintOptions());

   private:
    std::unique_ptr<Node> graph_;
};

}  // namespace bananas
