#include "bananagrams/bananagrams.hpp"

#include <algorithm>
#include <iostream>

#include "bananagrams/board.hpp"
#include "bananagrams/dictionary.hpp"
#include "helpers.hpp"

int main() {
    bananas::DictionaryFindOptions options;
    options.frequency_range = {99, 100};
    options.length_range = {3, -1};
    options.dictionary_file = bananas::resolvePath("dictionaries/en_1.txt");
    bananas::Dictionary dict{options};

    std::string chars = "aksdhfoweroweounsdkfnaweyuruewliuoiiioi";
    std::transform(chars.begin(), chars.end(), chars.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    auto board = bananas::play(options, chars);
    std::cout << board << std::endl;
}
