#include "charmap.hpp"

namespace bananas {

CharMap::CharMap(const std::string& characters) {
    *this += characters;
}

bool CharMap::has(char c) { return map_.find(c) != map_.end(); }

int& CharMap::at(char c) & { return map_.at(c); }

int CharMap::at(char c) const&& { return map_.at(c); }

} // namespace bananas
