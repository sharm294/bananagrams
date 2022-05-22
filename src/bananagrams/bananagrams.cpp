#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

#include "board.hpp"
#include "charmap.hpp"
#include "dictionary.hpp"
#include "node.hpp"

namespace bananas {

Board play(const std::string& dictionary_path, const std::string& characters) {
    CharMap chars(characters);
    Dictionary dict(dictionary_path);
    DictionaryFindOptions options;

    // auto words = dict.findWords(chars, options);
    Board board(&dict);

    std::stack<std::pair<size_t, size_t>> indices;
    indices.push({0, 0});
    do {
        auto& [index, offset] = indices.top();
        // if we exhausted all the words we had, we need to backtrack
        // if (index >= words.size()) {
        //     if (indices.size() == 1) {
        //         std::cout << "Could not find solution" << std::endl;
        //         return board;
        //     }
        //     auto removed_chars = board.removeLastWord();
        //     chars += removed_chars;
        //     words = dict.findWords(chars, options);
        //     indices.pop();
        //     indices.top().second++;
        //     continue;
        // }
        auto [played_chars, failure] =
          board.playWord(chars, options, index, offset);
        if (!played_chars.empty()) {
            std::cout << board << std::endl;
            chars -= played_chars;
            indices.push({0, 0});
        } else if (failure == -1) {
            if (indices.size() == 1) {
                std::cout << "Could not find solution" << std::endl;
                return board;
            }
            auto removed_chars = board.removeLastWord();
            chars += removed_chars;
            indices.pop();
            indices.top().second++;  // increment offset
        } else if (failure == 0) {
            index++;
            offset = 0;
        } else {
        }

        // else if (offset > 0) {
        //     index++;
        //     offset = 0;
        // } else {
        //     offset++;
        // }
    } while (!chars.empty());
    return board;
}

}  // namespace bananas
