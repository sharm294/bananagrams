#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <string>

#include "board.hpp"
#include "charmap.hpp"
#include "dictionary.hpp"
#include "node.hpp"

namespace bananas {

Board play(const std::string& dictionary_path,
           const DictionaryFindOptions& options,
           const std::string& characters) {
    CharMap chars(characters);
    Dictionary dict(dictionary_path);

    Board board(&dict);

    // maintain the state (word_index and position_index of each played) so
    // we can keep track on backtracking
    std::stack<std::pair<size_t, size_t>> state;
    state.push({0, 0});
    do {
        auto& [word_offset, position_offset] = state.top();
        auto [played_chars, retval] =
          board.playWord(chars, options, word_offset, position_offset);
        switch (retval) {
            case PlayWordState::kSuccess:
                assert(!played_chars.empty());
                // std::cout << board << std::endl;
                chars -= played_chars;
                state.push({0, 0});
                break;
            case PlayWordState::kWordIndexError:
                // if the first word played is giving us this error, we have
                // no valid solution given the characters and constraints
                if (state.size() == 1) {
                    std::cout << "Could not find solution" << std::endl;
                    return board;
                }
                chars += board.removeLastWord();
                state.pop();
                state.top().second++;  // increment position offset
                break;
            case PlayWordState::kWordPositionError:
                word_offset++;
                position_offset = 0;
                break;
            default:
                assert(false);
        }
    } while (!chars.empty());
    return board;
}

}  // namespace bananas
