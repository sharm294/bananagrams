#include "bananagrams/graph.hpp"

#include <iostream>

#include "bananagrams/charmap.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "helpers.hpp"

namespace bananas {

SCENARIO("Finding all anagrams") {
    GIVEN("A list of words") {
        auto path = resolvePath("tests/test_words.txt");
        Graph graph(path);

        WHEN("Search string is 'abder'") {
            CharMap chars("abder");
            auto words = graph.findWords(chars);
            std::vector<std::string> golden = {"bare", "bar"};
            REQUIRE(words == golden);
        }

        WHEN("Search string is 'basstec'") {
            CharMap chars("basstec");
            auto words = graph.findWords(chars);
            std::vector<std::string> golden = {"caste", "cast", "bast",
                                               "bass",  "cat",  "bat"};
            REQUIRE(words == golden);
        }
    }
}

SCENARIO("Checking if it's a word") {
    GIVEN("A list of words") {
        auto path = resolvePath("tests/test_words.txt");
        Graph graph(path);

        WHEN("Search string is 'bar'") { REQUIRE(graph.isWord("bar") == true); }

        WHEN("Search string is 'bareyl'") {
            REQUIRE(graph.isWord("bareyl") == false);
        }

        WHEN("Search string is 'ba'") { REQUIRE(graph.isWord("ba") == false); }
    }
}

// TEST_CASE("foo") {
//     auto path = resolvePath("tests/all_words.txt");
//     auto root = initializeGraph(path);
//     auto words = findWords(root.get(), "bardieiasdde");
//     for (const auto& word : words) {
//         std::cout << word << "\n";
//     }
// }

}  // namespace bananas

// int main() {
//     bananas::printTest1();
//     return 0;
// }
