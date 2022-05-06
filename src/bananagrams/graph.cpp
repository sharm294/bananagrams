#include "graph.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

namespace bananas {

std::unique_ptr<Node> initializeGraph(const std::string& path_to_words_file) {
    auto root = std::make_unique<Node>("");

    std::ifstream word_file(path_to_words_file);
    std::string word;
    while (word_file >> word) {
        auto* current_node = root.get();
        for (const auto& c : word) {
            Node* next = current_node->next(c);
            if (next == nullptr) {
                next = current_node->add(c);
            }
            current_node = next;
        }
        current_node->setValid();
    }

    return root;
}

void printAsTree(Node* root, const std::string& indent, const size_t max_depth,
                 std::ostream& stream) {
    auto word = root->getWord();
    auto next_indent = indent;
    if (!word.empty()) {
        stream << indent << word.back();
        if (root->isValid()) {
            stream << "*";
        }
        stream << "\n";
        next_indent += " ";
    }
    if (next_indent.length() > max_depth - 1) {
        return;
    }
    for (const auto& [c, next] : *root) {
        printAsTree(next.get(), next_indent, max_depth, stream);
    }
}

void printAsList(Node* root, std::ostream& stream) {
    if (root->isValid()) {
        stream << root->getWord() << "\n";
    }
    for (const auto& [c, next] : *root) {
        printAsList(next.get(), stream);
    }
}

void printGraph(Node* root, const GraphPrintOptions& options) {
    using Style = GraphPrintOptions::Style;

    auto& stream = options.stream;
    switch (options.style) {
        case Style::kTree: {
            const auto max_depth = options.depth < 1
                                     ? std::numeric_limits<size_t>::max()
                                     : options.depth;
            printAsTree(root, "", max_depth, stream);
            break;
        }
        case Style::kList: {
            printAsList(root, stream);
            break;
        }
    }
}

}  // namespace bananas
