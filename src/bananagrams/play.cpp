#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <stack>
#include <string>

#include "bananagrams/bananagrams.hpp"
#include "bananagrams/board.hpp"
#include "bananagrams/charmap.hpp"
#include "bananagrams/dictionary.hpp"
#include "bananagrams/node.hpp"

namespace bananas {

Board play(const DictionaryFindOptions& options, const std::string& characters,
           int64_t time_limit) {
    CharMap chars(characters);

    Dictionary dict(options);
    Board board(&dict);

    auto now = std::chrono::system_clock::now();
    bool timed_out = false;

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
                    board.clear();
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
        if (time_limit != 0) {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - now;
            timed_out = elapsed_seconds.count() > time_limit;
        }
    } while ((!chars.empty()) && (!timed_out));

    if (timed_out) {
        std::cout << "No solution found in time limit\n";
        board.clear();
    }

    return board;
}

Board play(const DictionaryFindOptions& options,
           const std::string& characters) {
    return play(options, characters, 0);
}

}  // namespace bananas
