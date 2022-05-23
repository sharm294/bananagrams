#include "bananagrams/dictionary.hpp"

#include <iostream>

#include "bananagrams/charmap.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "helpers.hpp"

namespace bananas {

SCENARIO("Finding all anagrams") {
    GIVEN("A list of words") {
        auto path = resolvePath("tests/test_words.txt");
        Dictionary dict(path);
        DictionaryFindOptions options;

        WHEN("Search string is 'abder'") {
            CharMap chars("abder");
            auto words = dict.findWords(chars, options);
            StringVector golden = {
              "bare",
              "bard",
              "bar",
            };
            REQUIRE(words == golden);
        }

        WHEN("Search string is 'basstec'") {
            CharMap chars("basstec");
            auto words = dict.findWords(chars, options);
            StringVector golden = {"caste", "cast", "bast",
                                   "bass",  "cat",  "bat"};
            REQUIRE(words == golden);
        }
    }
}

SCENARIO("Checking if it's a word") {
    GIVEN("A list of words") {
        auto path = resolvePath("tests/test_words.txt");
        Dictionary dict(path);

        WHEN("Search string is 'bar'") { REQUIRE(dict.isWord("bar") == true); }

        WHEN("Search string is 'bareyl'") {
            REQUIRE(dict.isWord("bareyl") == false);
        }

        WHEN("Search string is 'ba'") { REQUIRE(dict.isWord("ba") == false); }
    }
}

SCENARIO("One of pass") {
    GIVEN("A list of words") {
        auto path = resolvePath("tests/test_words.txt");
        Dictionary dict(path);

        WHEN("Search string is 'abder' and must contain 'e'") {
            CharMap chars("abder");
            DictionaryFindOptions options;
            options.one_of.emplace_back("e");
            auto words = dict.findWords(chars, options);
            StringVector golden = {"bare"};
            REQUIRE(words == golden);
        }

        WHEN("Search string is 'basstec' and must contain 'c' or 's'") {
            CharMap chars("basstec");
            DictionaryFindOptions options;
            options.one_of.emplace_back("c");
            options.one_of.emplace_back("s");
            auto words = dict.findWords(chars, options);
            StringVector golden = {"caste", "cast", "bast", "bass", "cat"};
            REQUIRE(words == golden);
        }
    }
}

}  // namespace bananas
