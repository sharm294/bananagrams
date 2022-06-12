#include <algorithm>
#include <cassert>
#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "bananagrams/bananagrams.hpp"
#include "bananagrams/board.hpp"
#include "bananagrams/dictionary.hpp"

int main(int argc, char* argv[]) {
    cxxopts::Options options("Bananagrams", "Bananagram solver");

    std::vector<std::string> positionals;
    float freq_min = 0;
    float freq_max = 0;
    int len_min = 0;
    int len_max = 0;
    int64_t time_limit = 0;
    // clang-format off
    options.add_options()
      ("positionals", "", cxxopts::value<std::vector<std::string>>(positionals))
      ("freq-min", "Minimum frequency as a percentage",
        cxxopts::value<float>(freq_min))
      ("freq-max", "Maximum frequency as a percentage",
        cxxopts::value<float>(freq_max))
      ("len-min", "Minimum word length", cxxopts::value<int>(len_min))
      ("len-max", "Maximum word length", cxxopts::value<int>(len_max))
      ("time-limit", "Max time to search in seconds",
        cxxopts::value<int64_t>(time_limit))
      ("h,help", "Print usage");
    // clang-format on

    options.parse_positional("positionals");
    options.positional_help("path_to_dictionary characters");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    bananas::DictionaryFindOptions banana_options;
    banana_options.frequency_range = {freq_min, freq_max};
    banana_options.length_range = {len_min, len_max};
    banana_options.dictionary_file = positionals[0];

    auto& chars = positionals[1];
    std::transform(chars.begin(), chars.end(), chars.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    auto board = bananas::play(banana_options, chars, time_limit);
    std::cout << board << std::endl;

    return 0;
}
