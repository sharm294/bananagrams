#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
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
using StringVector = std::vector<std::string>;

struct DictionaryPrintOptions {
    enum Style { kTree, kList };

    // global options
    Style style = Style::kTree;
    std::ostream& stream = std::cout;

    // kTree options
    int depth = -1;
};

struct DictionaryFindOptions {
    // global options
    std::string dictionary_file;

    std::pair<float, float> frequency_range = {0, 0};
    std::pair<int, int> length_range = {0, 0};
};

class Dictionary {
   public:
    explicit Dictionary(DictionaryFindOptions options);

    bool isWord(const std::string& word) const;
    StringVector findWords(CharMap& characters,
                           const DictionaryFindOptions& options);
    void findWords(CharMap& characters, const DictionaryFindOptions& options,
                   StringVector* set);

    void print(
      const DictionaryPrintOptions& options = DictionaryPrintOptions()) const;

   private:
    DictionaryFindOptions options_;
    std::unique_ptr<Node> dict_;
    std::unordered_map<std::string, StringVector> cache_;
};

}  // namespace bananas
