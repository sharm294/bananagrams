#include "board.hpp"

#include "graph.hpp"
#include "node.hpp"

namespace bananas {

std::ostream &operator<<(std::ostream &os, const Point &self) {
    os << "(" << self.x << "," << self.y << ")";
    return os;
}

Board::Board(Graph *graph) : graph_(graph) {}

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

bool Board::tryPlace(const std::string &word, Point p, bool horizontal) {
    auto start = p;
    for (const auto &c : word) {
        if (this->has(p)) {
            auto *placed = this->at(p);
            if (*placed != c) {
                return false;
            }
        }
        if (horizontal) {
            updatePoint(p, Direction::kEast);
        } else {
            updatePoint(p, Direction::kSouth);
        }
    }
    if (horizontal) {
        this->insertWord(word, start, Direction::kEast);
    } else {
        this->insertWord(word, start, Direction::kSouth);
    }
    return true;
}

Point Board::getStartingPoint(Point p, bool horizontal) {
    // find start of word containing point p
    while (has(p)) {
        if (horizontal) {
            updatePoint(p, Direction::kWest);
        } else {
            updatePoint(p, Direction::kNorth);
        }
    }
    // undo last update
    if (horizontal) {
        updatePoint(p, Direction::kEast);
    } else {
        updatePoint(p, Direction::kSouth);
    }
    return p;
}

bool hasAdjacentTiles(Board *board, Point p, bool horizontal) {
    Point adjacent_0 = p;
    Point adjacent_1 = p;

    if (horizontal) {
        updatePoint(adjacent_0, Direction::kWest);
        updatePoint(adjacent_1, Direction::kEast);
    } else {
        updatePoint(adjacent_0, Direction::kNorth);
        updatePoint(adjacent_1, Direction::kSouth);
    }

    return board->has(adjacent_0) && board->has(adjacent_1);
}

void Board::removeLastWord() {
    auto &last = history_.top();
    for (const auto &p : last) {
        board_.erase(p);
    }
    history_.pop();
}

std::string Board::getWord(Point p, bool horizontal) {
    p = getStartingPoint(p, horizontal);

    std::string s;
    while (has(p)) {
        s += *(this->at(p));
        if (horizontal) {
            updatePoint(p, Direction::kEast);
        } else {
            updatePoint(p, Direction::kSouth);
        }
    }
    return s;
}

template <bool horizontal>
bool tryHorizontal(Board *board, Point connection_point,
                   const std::string &word, Graph *root) {
    // early exit if both adjacent tiles are blocked
    if (hasAdjacentTiles(board, connection_point, horizontal)) {
        return false;
    }

    auto *c = board->at(connection_point);
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
        if (board->tryPlace(word, starting_point, horizontal)) {
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
                auto str = board->getWord(curr_point, !horizontal);
                if (str.length() > 1 && !root->isWord(str)) {
                    board->removeLastWord();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool Board::playWord(const std::string &word) {
    // if board is currently empty, play word at origin
    if (board_.find({0, 0}) == board_.end()) {
        insertWord(word, {0, 0}, Direction::kEast);
        return true;
    }

    // otherwise, there's at least one word in play and we need to search for
    // legal positions
    auto board_copy = board_;
    for (const auto &[point, c] : board_copy) {
        if (tryHorizontal<true>(this, point, word, this->graph_)) {
            return true;
        }
        if (tryHorizontal<false>(this, point, word, this->graph_)) {
            return true;
        }
    }
    return false;
}

void Board::insertWord(const std::string &word, Point start,
                       Direction direction) {
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
