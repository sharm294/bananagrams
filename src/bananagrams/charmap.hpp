#pragma once

#include <string>
#include <unordered_map>

namespace bananas {

class CharMap {
   public:
    explicit CharMap(const std::string& characters);

    bool has(char c) const;
    bool empty() const;

    int& at(char c) &;
    int at(char c) const&&;

    CharMap& operator+=(const char& rhs) {
        if (map_.find(rhs) != map_.end()) {
            map_.at(rhs) += 1;
        } else {
            map_.insert({rhs, 1});
        }
        return *this;
    }

    CharMap& operator+=(const std::string& rhs) {
        for (const auto& c : rhs) {
            *this += c;
        }
        return *this;
    }

    CharMap& operator-=(const char& rhs) {
        if (map_.find(rhs) != map_.end()) {
            if (map_.at(rhs) > 1) {
                --map_.at(rhs);
            } else {
                map_.erase(rhs);
            }
        }
        return *this;
    }

    CharMap& operator-=(const std::string& rhs) {
        for (const auto& c : rhs) {
            *this -= c;
        }
        return *this;
    }

   private:
    std::unordered_map<char, int> map_;
};

template <typename T>
inline CharMap operator+(CharMap lhs, const T& rhs) {
    lhs += rhs;
    return lhs;
}

template <typename T>
inline CharMap operator-(CharMap lhs, const T& rhs) {
    lhs -= rhs;
    return lhs;
}

}  // namespace bananas
