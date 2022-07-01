#include "bananagrams/bananagrams.hpp"

#include <cstring>

#include "bananagrams/board.hpp"
#include "bananagrams/play.hpp"

char* c_play(DictionaryFindOptions* options, char* chars, unsigned int char_num,
             int time_constraint, int& num_tiles) {
    bananas::DictionaryFindOptions options_cpp{*options};
    auto board =
      bananas::play(options_cpp, std::string{chars, char_num}, time_constraint);

    auto board_str = board.serialize();

    num_tiles = board_str.size();
    char* out = new char[num_tiles];
    strcpy(out, board_str.c_str());
    return out;
}

namespace bananas {

std::string cpp_play(const DictionaryFindOptions& options,
                     const std::string& chars, int time_constraint) {
    auto board = bananas::play(options, chars, time_constraint);
    return board.serialize();
}

}  // namespace bananas
