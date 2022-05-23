#pragma once

#include <string>

namespace bananas {

class Board;
class Dictionary;
class DictionaryFindOptions;

Board play(const Dictionary& dict,
           const DictionaryFindOptions& options, const std::string& characters);

}  // namespace bananas
