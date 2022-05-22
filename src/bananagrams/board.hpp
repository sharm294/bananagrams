#pragma once

#include <cstdint>
#include <ostream>
#include <set>
#include <stack>
#include <unordered_map>

#include "point.hpp"

namespace bananas {

class CharMap;
class Dictionary;
class DictionaryFindOptions;

enum class Direction { kNorth, kEast, kSouth, kWest };

class Board {
   public:
    explicit Board(Dictionary *dict);

    // return value is word played (empty if nothing) and whether we failed
    // because: ran out of words (-1), index failed (0), offset failed (>0),
    // don't care (-2)
    std::pair<std::string, int> playWord(CharMap characters,
                                          const DictionaryFindOptions &options,
                                          size_t word_offset,
                                          size_t position_offset);
    std::string removeLastWord();

    char *at(Point p);
    bool has(Point p);

    friend std::ostream &operator<<(std::ostream &os, const Board &self);

   private:
    void insertWord(const std::string &word, Point start, Direction direction);
    std::string getLastWord();

    template <bool horizontal>
    bool tryPlace(const std::string &word, Point p);

    template <bool horizontal>
    bool tryHorizontal(Point connection_point, const std::string &word,
                       size_t offset);

    std::unordered_map<Point, char, PointHash> board_;
    Dictionary *dict_;
    std::stack<std::set<Point>> history_;
};

}  // namespace bananas
