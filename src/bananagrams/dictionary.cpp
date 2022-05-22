#include "dictionary.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "charmap.hpp"

namespace bananas {

Dictionary::Dictionary(const std::string& path_to_words_file) {
    dict_ = std::make_unique<Node>("");

    std::ifstream word_file(path_to_words_file);
    std::string word;
    while (word_file >> word) {
        auto* current_node = dict_.get();
        for (const auto& c : word) {
            Node* next = current_node->next(c);
            if (next == nullptr) {
                next = current_node->add(c);
            }
            current_node = next;
        }
        current_node->setValid();
    }
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

void Dictionary::print(const DictionaryPrintOptions& options) {
    using Style = DictionaryPrintOptions::Style;

    auto& stream = options.stream;
    switch (options.style) {
        case Style::kTree: {
            const auto max_depth = options.depth < 1
                                     ? std::numeric_limits<size_t>::max()
                                     : options.depth;
            printAsTree(dict_.get(), "", max_depth, stream);
            break;
        }
        case Style::kList: {
            printAsList(dict_.get(), stream);
            break;
        }
    }
}

/**
 * @brief Check if the word contains at least one of the substrings
 *
 * @param word
 * @param one_of vector of strings to check
 * @return true if found at least one
 */
bool oneOfPass(const std::string& word,
               const std::vector<std::string>& one_of) {
    // if we have no conditions, we always pass
    if (one_of.empty()) {
        return true;
    }

    // otherwise, we check if we have at least one match
    for (const auto& str : one_of) {
        if (word.find(str) != word.npos) {
            return true;
        }
    }
    return false;
}

bool checkValid(const std::string& word, const DictionaryFindOptions& options) {
    if (!oneOfPass(word, options.one_of)) {
        return false;
    }
    return true;
}

void search(Node* root, CharMap* map, const DictionaryFindOptions& options,
            StringSet* found_words) {
    if (root->isValid()) {
        auto& word = root->getWord();
        if (checkValid(word, options)) {
            found_words->emplace_back(word);
        }
    }
    for (const auto& [c, next] : *root) {
        if (map->has(c) && map->at(c) > 0) {
            map->at(c)--;
            search(next.get(), map, options, found_words);
            map->at(c)++;
        }
    }
}

std::vector<std::string> toVector(const StringSet& set) {
    std::vector<std::string> output(set.begin(), set.end());
    return output;
}

bool sortWords(const std::string& lhs, const std::string& rhs) {
    if (lhs.length() != rhs.length()) {
        return lhs.length() > rhs.length();
    }
    return lhs > rhs;
}

StringSet Dictionary::findWords(CharMap characters,
                                const DictionaryFindOptions& options) {
    StringSet found_words;
    search(dict_.get(), &characters, options, &found_words);
    return found_words;
}

void Dictionary::findWords(CharMap characters,
                           const DictionaryFindOptions& options,
                           StringSet* set) {
    search(dict_.get(), &characters, options, set);
}

bool Dictionary::isWord(const std::string& word) {
    auto* curr_node = dict_.get();
    for (const auto& c : word) {
        curr_node = curr_node->next(c);
        if (curr_node == nullptr) {
            return false;
        }
    }
    return curr_node->isValid();
}

}  // namespace bananas
