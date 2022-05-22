#pragma once

#include <string>

namespace bananas {

class Board;

Board play(const std::string& dictionary_path, const std::string& characters);

}  // namespace bananas
