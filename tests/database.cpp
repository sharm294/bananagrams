#include <bananagrams/database.hpp>

namespace bananas {

void printTest0(){
    auto root = initializeGraph("test_words.txt");
    root->print("");
}

}

int main(){
    bananas::printTest0();
    return 0;
}
