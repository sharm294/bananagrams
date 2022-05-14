#pragma once

#include <string>
#include <unordered_map>

namespace bananas {

class CharMap {
   public:
    explicit CharMap(const std::string& characters);

    bool has(char c);

    int& at(char c) &;
    int at(char c) const&&;

    CharMap& operator+=(const std::string& rhs) {
        for (const auto& c : rhs) {
            if (map_.find(c) != map_.end()) {
                ++map_.at(c);
            } else {
                map_.insert({c, 1});
            }
        }
        return *this;
    }

    CharMap& operator-=(const std::string& rhs) {
        for (const auto& c : rhs) {
            if (map_.find(c) != map_.end()) {
                if (map_.at(c) > 0) {
                    --map_.at(c);
                } else {
                    map_.erase(c);
                }
            }
        }
        return *this;
    }

   private:
    std::unordered_map<char, int> map_;
};

inline CharMap operator+(CharMap lhs, const std::string& rhs) {
    lhs += rhs;
    return lhs;
}

inline CharMap operator-(CharMap lhs, const std::string& rhs) {
    lhs -= rhs;
    return lhs;
}

}  // namespace bananas
