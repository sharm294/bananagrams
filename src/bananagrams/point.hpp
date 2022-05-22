#pragma once

namespace bananas {

struct Point {
    int16_t x;
    int16_t y;

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

inline std::ostream &operator<<(std::ostream &os, const Point &self) {
    os << "(" << self.x << "," << self.y << ")";
    return os;
}

}  // namespace bananas
