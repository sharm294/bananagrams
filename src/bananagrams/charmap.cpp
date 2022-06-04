#include "charmap.hpp"

namespace bananas {

CharMap::CharMap(const std::string& characters) { *this += characters; }

bool CharMap::has(char c) const { return map_.find(c) != map_.end(); }

bool CharMap::empty() const { return map_.empty(); }

int& CharMap::at(char c) & { return map_.at(c); }

int CharMap::at(char c) const&& { return map_.at(c); }

std::string CharMap::str() const {
    std::string str;
    for (const auto& [c, count] : map_) {
        for (auto i = 0; i < count; i++) {
            str.push_back(c);
        }
    }
    return str;
}

std::unordered_map<char, int>::iterator CharMap::begin() {
    return map_.begin();
}

std::unordered_map<char, int>::iterator CharMap::end() { return map_.end(); }

std::unordered_map<char, int>::const_iterator CharMap::cbegin() const {
    return map_.cbegin();
}

std::unordered_map<char, int>::const_iterator CharMap::cend() const {
    return map_.cend();
}

}  // namespace bananas
