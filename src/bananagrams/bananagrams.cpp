#include <cassert>
#include <string>

#include "board.hpp"
#include "dictionary.hpp"
#include "node.hpp"

namespace bananas {

// bool iteration(Board* board, const std::vector<std::string>& words,
//                CharMap characters) {
//     assert(board != nullptr);

//     for (const auto& word : words) {
//         // iteration()
//     }
// }

Board play(Node* root, const std::string& characters) {
    assert(root != nullptr);

    CharMap chars(characters);

    auto words = findWords(root, chars);
    int index = 0;
    do {
        Board board(words[index]);
        chars -= words[index];
        // iteration(&board, words, chars);
    } while (true);
}

}  // namespace bananas
