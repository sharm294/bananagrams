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

Dictionary::Dictionary(DictionaryFindOptions options)
  : options_(std::move(options)) {
    dict_ = std::make_unique<Node>("");

    std::ifstream word_file(options_.dictionary_file);
    std::string word;
    float frequency;
    while (word_file >> word >> frequency) {
        auto* current_node = dict_.get();
        for (const auto& c : word) {
            Node* next = current_node->next(c);
            if (next == nullptr) {
                next = current_node->add(c);
            }
            current_node = next;
        }
        current_node->setValid();
        current_node->setFrequency(frequency);
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

void Dictionary::print(const DictionaryPrintOptions& options) const {
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
bool oneOfPass(Node* node, const std::vector<std::string>& one_of) {
    // if we have no conditions, we always pass
    if (one_of.empty()) {
        return true;
    }

    // otherwise, we check if we have at least one match
    const auto& word = node->getWord();
    for (const auto& str : one_of) {
        if (word.find(str) != word.npos) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool checkInRange(T value, T min, T max) {
    // if undefined, return true
    if (min == 0 && max == 0) {
        return true;
    }

    // if there's no min constraint, just check max
    if (min <= 0 && max > 0) {
        return value <= max;
    }

    // if there's no max constraint, just check min
    if (max <= 0) {
        return value >= min;
    }

    // otherwise, check the range
    return value >= min && value <= max;
}

bool frequencyPass(Node* node, std::pair<float, float> frequency_range) {
    auto frequency = node->getFrequency();

    return checkInRange<float>(frequency, frequency_range.first,
                               frequency_range.second);
}

bool lengthPass(Node* node, std::pair<int, int> length_range) {
    auto len = static_cast<int>(node->getWord().length());

    return checkInRange<int>(len, length_range.first, length_range.second);
}

bool checkValid(Node* node, const DictionaryFindOptions& options) {
    if (!oneOfPass(node, options.one_of)) {
        return false;
    }

    if (!frequencyPass(node, options.frequency_range)) {
        return false;
    }

    if (!lengthPass(node, options.length_range)) {
        return false;
    }

    return true;
}

void search(Node* root, CharMap* map, const DictionaryFindOptions& options,
            StringVector* found_words) {
    if (root->isValid()) {
        if (checkValid(root, options)) {
            found_words->emplace_back(root->getWord());
        }
    }
    for (const auto& [c, count] : *map) {
        auto* next = root->next(c);
        if (count > 0 && next != nullptr) {
            map->at(c)--;
            search(next, map, options, found_words);
            map->at(c)++;
        }
    }
}

bool sortWords(const std::string& lhs, const std::string& rhs) {
    if (lhs.length() != rhs.length()) {
        return lhs.length() > rhs.length();
    }
    return lhs > rhs;
}

StringVector Dictionary::findWords(CharMap characters,
                                   const DictionaryFindOptions& options) const {
    StringVector found_words;
    search(dict_.get(), &characters, options, &found_words);
    return found_words;
}

void Dictionary::findWords(CharMap characters,
                           const DictionaryFindOptions& options,
                           StringVector* vector) const {
    search(dict_.get(), &characters, options, vector);
}

bool Dictionary::isWord(const std::string& word) const {
    auto* curr_node = dict_.get();
    for (const auto& c : word) {
        curr_node = curr_node->next(c);
        if (curr_node == nullptr) {
            return false;
        }
    }
    if (!curr_node->isValid()) {
        return false;
    }
    return checkValid(curr_node, this->options_);
}

}  // namespace bananas
