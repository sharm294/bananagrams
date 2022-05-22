#include "charmap.hpp"

namespace bananas {

CharMap::CharMap(const std::string& characters) {
    *this += characters;
}

bool CharMap::has(char c) const { return map_.find(c) != map_.end(); }

bool CharMap::empty() const { return map_.empty(); }

int& CharMap::at(char c) & { return map_.at(c); }

int CharMap::at(char c) const&& { return map_.at(c); }

} // namespace bananas
