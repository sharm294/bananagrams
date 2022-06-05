#pragma once

#include <string>

namespace bananas {

class Board;
class DictionaryFindOptions;

Board play(const DictionaryFindOptions& options, const std::string& characters);

}  // namespace bananas
