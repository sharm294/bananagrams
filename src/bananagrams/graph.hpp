#pragma once

#include <iostream>
#include <string>

#include "node.hpp"

namespace bananas {

/**
 * @brief Given a path to a text file with words, construct a graph and return
 * a pointer to the root
 *
 * @param path_to_words_file path to a file containing words separated by
 * newlines
 * @return std::unique_ptr<Node>
 */
std::unique_ptr<Node> initializeGraph(const std::string& path_to_words_file);

struct GraphPrintOptions {
    enum Style { kTree, kList };

    // global options
    Style style = Style::kTree;
    std::ostream& stream = std::cout;

    // kTree options
    int depth = -1;
};

/**
 * @brief
 *
 * @param root
 * @param indent
 * @param stream
 */
void printGraph(Node* root,
                const GraphPrintOptions& options = GraphPrintOptions());

}  // namespace bananas
