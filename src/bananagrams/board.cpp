#include "board.hpp"

#include <algorithm>
#include <cassert>

#include "charmap.hpp"
#include "dictionary.hpp"
#include "node.hpp"
#include "point.hpp"

namespace bananas {

Board::Board(Dictionary *dict) : dict_(dict) {}

char *Board::at(Point p) {
    if (!this->has(p)) {
        return nullptr;
    }
    return &(board_.at(p));
}

bool Board::has(Point p) { return board_.find(p) != board_.end(); }

void updatePoint(Point &p, Direction direction) {
    switch (direction) {
        case Direction::kNorth:
            --p.y;
            break;
        case Direction::kEast:
            ++p.x;
            break;
        case Direction::kSouth:
            ++p.y;
            break;
        case Direction::kWest:
            --p.x;
            break;
    }
}

template <bool horizontal>
bool Board::tryPlace(const std::string &word, Point p) {
    auto start = p;
    bool played = false;  // prevent playing the same word over itself
    for (const auto &c : word) {
        if (this->has(p)) {
            auto *placed = this->at(p);
            if (*placed != c) {
                return false;
            }
        } else {
            played = true;  // make sure at least one new character is played
        }
        if constexpr (horizontal) {
            updatePoint(p, Direction::kEast);
        } else {
            updatePoint(p, Direction::kSouth);
        }
    }
    if (!played) {
        return false;
    }
    if constexpr (horizontal) {
        this->insertWord(word, start, Direction::kEast);
    } else {
        this->insertWord(word, start, Direction::kSouth);
    }
    return true;
}

template <bool horizontal>
Point getStartingPoint(Board *board, Point p) {
    // find start of word containing point p
    while (board->has(p)) {
        if constexpr (horizontal) {
            updatePoint(p, Direction::kWest);
        } else {
            updatePoint(p, Direction::kNorth);
        }
    }
    // undo last update
    if constexpr (horizontal) {
        updatePoint(p, Direction::kEast);
    } else {
        updatePoint(p, Direction::kSouth);
    }
    return p;
}

template <bool horizontal>
bool hasAdjacentTiles(Board *board, Point p) {
    Point adjacent_0 = p;
    Point adjacent_1 = p;

    if constexpr (horizontal) {
        updatePoint(adjacent_0, Direction::kWest);
        updatePoint(adjacent_1, Direction::kEast);
    } else {
        updatePoint(adjacent_0, Direction::kNorth);
        updatePoint(adjacent_1, Direction::kSouth);
    }

    return board->has(adjacent_0) && board->has(adjacent_1);
}

std::string Board::removeLastWord() {
    auto &last = history_.top();
    std::string removed_chars;
    for (const auto &p : last) {
        removed_chars += board_[p];
        board_.erase(p);
    }
    history_.pop();
    return removed_chars;
}

/**
 * @brief Given a point and a direction, get the word containing this point
 *
 * @param p a point
 * @return std::string
 */
template <bool horizontal>
std::string getWord(Board *board, Point p) {
    p = getStartingPoint<horizontal>(board, p);

    std::string s;
    while (board->has(p)) {
        s += *(board->at(p));
        if constexpr (horizontal) {
            updatePoint(p, Direction::kEast);
        } else {
            updatePoint(p, Direction::kSouth);
        }
    }
    return s;
}

template <bool horizontal>
bool Board::tryHorizontal(Point connection_point, const std::string &word,
                          size_t offset) {
    // early exit if both adjacent tiles are blocked
    if (hasAdjacentTiles<horizontal>(this, connection_point)) {
        return false;
    }

    auto *c = this->at(connection_point);
    for (auto i = 0U; i < word.length(); ++i) {
        if (*c != word[i]) {
            continue;
        }
        Point starting_point;
        if constexpr (horizontal) {
            starting_point = connection_point - std::make_pair(i, 0);
        } else {
            starting_point = connection_point - std::make_pair(0, i);
        }
        if (this->tryPlace<horizontal>(word, starting_point)) {
            // if successful, check the word in the same direction
            auto read_word = getWord<horizontal>(this, starting_point);
            if (!dict_->isWord(read_word)) {
                this->removeLastWord();
                return false;
            }

            // if the same direction succeeds, also check all words made
            // perpendicular to the new one
            for (auto j = 0U; j < word.length(); ++j) {
                Point curr_point;
                if constexpr (horizontal) {
                    curr_point = starting_point + std::make_pair(j, 0);
                } else {
                    curr_point = starting_point + std::make_pair(0, j);
                }
                // if the point we're considering is where the new word meets
                // the board, we can skip it because we already know the word
                // there is valid
                if (curr_point == connection_point) {
                    continue;
                }
                auto str = getWord<!horizontal>(this, curr_point);
                if (str.length() > 1 && !dict_->isWord(str)) {
                    this->removeLastWord();
                    return false;
                }
            }
            // we need to be able to try multiple valid positions that are
            // possible, not just the first one
            if (offset == 0) {
                return true;
            } else {
                this->removeLastWord();
                --offset;
            }
        }
    }
    return false;
}

std::string Board::getLastWord() {
    auto &last = history_.top();
    std::string chars;
    for (const auto &p : last) {
        chars += board_[p];
    }
    return chars;
}

PlayWordResult Board::playWord(CharMap characters,
                               const DictionaryFindOptions &options,
                               size_t word_offset, size_t position_offset) {
    // if board is currently empty, play word at origin
    if (board_.empty()) {
        // if we're trying to play the first word somewhere else, early exit
        if (position_offset > 0) {
            return std::make_pair("", PlayWordState::kWordPositionError);
        }

        auto words = dict_->findWords(characters, options);
        std::sort(words.begin(), words.end(), sortWords);
        if (word_offset < words.size()) {
            auto &word = words[word_offset];
            insertWord(word, {0, 0}, Direction::kEast);
            return std::make_pair(word, PlayWordState::kSuccess);
        } else {
            return std::make_pair("", PlayWordState::kWordIndexError);
        }
    }

    // otherwise, there's at least one word in play and we need to search for
    // legal positions
    StringVector words_tmp;
    std::vector<std::pair<std::string, Point>> words;
    // TODO: we need to find the word (horizontal and vertical) at each point
    // and add that to options so we can find words that include substrings
    for (const auto &[point, c] : board_) {
        characters += c;
        StringVector words_tmp;
        dict_->findWords(characters, options, &words_tmp);
        characters -= c;
        const auto &point_copy = point;
        std::transform(words_tmp.cbegin(), words_tmp.cend(),
                       std::back_inserter(words),
                       [&point_copy](const std::string &word) {
                           return std::make_pair(word, point_copy);
                       });
    }
    std::sort(words.begin(), words.end(),
              [](const std::pair<std::string, Point> &lhs,
                 const std::pair<std::string, Point> &rhs) {
                  const auto &lhs_str = lhs.first;
                  const auto &rhs_str = rhs.first;

                  return sortWords(lhs_str, rhs_str);
              });

    if (word_offset >= words.size()) {
        return std::make_pair("", PlayWordState::kWordIndexError);
    }
    auto &word = words[word_offset].first;
    auto &point = words[word_offset].second;

    // try to play it horizontally
    if (this->tryHorizontal<true>(point, word, position_offset)) {
        return std::make_pair(getLastWord(), PlayWordState::kSuccess);
    }
    // try to play it vertically
    if (this->tryHorizontal<false>(point, word, position_offset)) {
        return std::make_pair(getLastWord(), PlayWordState::kSuccess);
    }

    return std::make_pair("", PlayWordState::kWordPositionError);
}

void Board::insertWord(const std::string &word, Point start,
                       Direction direction) {
    assert(!word.empty());
    Point curr_point = start;
    history_.emplace();
    auto &top = history_.top();
    for (const auto &c : word) {
        if (!this->has(curr_point)) {
            board_[curr_point] = c;
            top.insert(curr_point);
        }
        updatePoint(curr_point, direction);
    }
}

std::ostream &operator<<(std::ostream &os, const Board &self) {
    // get board dimensions
    Point top_left = {0, 0};
    Point bottom_right = {0, 0};
    for (const auto &[point, c] : self.board_) {
        if (point.x < top_left.x) {
            top_left.x = point.x;
        }
        if (point.x > bottom_right.x) {
            bottom_right.x = point.x;
        }
        if (point.y < top_left.y) {
            top_left.y = point.y;
        }
        if (point.y > bottom_right.y) {
            bottom_right.y = point.y;
        }
    }

    // print board
    for (auto y = top_left.y; y <= bottom_right.y; ++y) {
        for (auto x = top_left.x; x <= bottom_right.x; ++x) {
            const auto point = self.board_.find({x, y});
            if (point == self.board_.end()) {
                os << " ";
            } else {
                os << point->second;
            }
            os << " ";
        }
        os << "\n";
    }

    return os;
}

}  // namespace bananas
