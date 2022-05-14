#pragma once

#include <cstdint>
#include <ostream>
#include <set>
#include <stack>
#include <unordered_map>

namespace bananas {

class Graph;

struct Point {
    int16_t x;
    int16_t y;

    friend std::ostream &operator<<(std::ostream &os, const Point &self);
    Point &operator+=(const std::pair<int, int> &rhs) {
        x += rhs.first;
        y += rhs.second;
        return *this;
    }

    Point &operator-=(const std::pair<int, int> &rhs) {
        x -= rhs.first;
        y -= rhs.second;
        return *this;
    }
};

struct PointHash {
    std::size_t operator()(const Point &p) const noexcept {
        return ((p.x << 16) | p.y);
    }
};

inline Point operator+(Point lhs, std::pair<int, int> rhs) {
    lhs.x += rhs.first;
    lhs.y += rhs.second;
    return lhs;
}

inline Point operator-(Point lhs, std::pair<int, int> rhs) {
    lhs.x -= rhs.first;
    lhs.y -= rhs.second;
    return lhs;
}

inline bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
inline bool operator!=(const Point &lhs, const Point &rhs) {
    return !operator==(lhs, rhs);
}
inline bool operator<(const Point &lhs, const Point &rhs) {
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    }
    return lhs.y < rhs.y;
}
inline bool operator>(const Point &lhs, const Point &rhs) {
    return operator<(rhs, lhs);
}
inline bool operator<=(const Point &lhs, const Point &rhs) {
    return !operator>(lhs, rhs);
}
inline bool operator>=(const Point &lhs, const Point &rhs) {
    return !operator<(lhs, rhs);
}

enum class Direction { kNorth, kEast, kSouth, kWest };

class Board {
   public:
    explicit Board(Graph *graph);

    bool playWord(const std::string &word);
    bool tryPlace(const std::string &word, Point p, bool horizontal);
    std::string getWord(Point p, bool horizontal);
    void removeLastWord();

    char *at(Point p);
    bool has(Point p);

    friend std::ostream &operator<<(std::ostream &os, const Board &self);

   private:
    void insertWord(const std::string &word, Point start, Direction direction);
    Point getStartingPoint(Point p, bool horizontal);

    std::unordered_map<Point, char, PointHash> board_;
    Graph *graph_;
    std::stack<std::set<Point>> history_;
};

}  // namespace bananas
