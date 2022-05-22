#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "node.hpp"

namespace bananas {

class CharMap;

bool sortWords(const std::string& lhs, const std::string& rhs);

struct WordSort {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return sortWords(lhs, rhs);
    }
};
using StringSet = std::vector<std::string>;

std::vector<std::string> toVector(const StringSet& set);

struct DictionaryPrintOptions {
    enum Style { kTree, kList };

    // global options
    Style style = Style::kTree;
    std::ostream& stream = std::cout;

    // kTree options
    int depth = -1;
};

struct DictionaryFindOptions {
    std::vector<std::string> one_of;
};

class Dictionary {
   public:
    explicit Dictionary(const std::string& path_to_words_file);

    bool isWord(const std::string& word);
    StringSet findWords(CharMap characters,
                        const DictionaryFindOptions& options);
    void findWords(CharMap characters, const DictionaryFindOptions& options,
                   StringSet* set);

    void print(
      const DictionaryPrintOptions& options = DictionaryPrintOptions());

   private:
    std::unique_ptr<Node> dict_;
};

}  // namespace bananas
