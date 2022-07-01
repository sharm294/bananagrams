#pragma once

#include <string>

#include "bananagrams.h"

namespace bananas {

struct DictionaryFindOptions {
    DictionaryFindOptions() = default;
    DictionaryFindOptions(::DictionaryFindOptions options) {
        dictionary_file =
          std::string{options.dictionary_file, options.dictionary_file_len};
        frequency_range = {options.freq_min, options.freq_max};
        length_range = {options.len_min, options.len_max};
    }

    std::string dictionary_file;

    std::pair<float, float> frequency_range = {0, 0};
    std::pair<int, int> length_range = {0, 0};
};

std::string cpp_play(const DictionaryFindOptions& options,
                     const std::string& chars, int time_constraint);

}  // namespace bananas
