#include "bananagrams/dictionary.hpp"

#include <algorithm>
#include <iostream>

#include "bananagrams/charmap.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "helpers.hpp"

namespace bananas {

SCENARIO("Finding all anagrams") {
    GIVEN("A list of words") {
        bananas::DictionaryFindOptions options;
        options.dictionary_file = bananas::resolvePath("tests/test_words.txt");
        Dictionary dict(options);

        WHEN("Search string is 'abder'") {
            CharMap chars("abder");
            auto words = dict.findWords(chars, options);
            StringVector golden = {
              "bare",
              "bard",
              "bar",
            };
            std::sort(words.begin(), words.end());
            std::sort(golden.begin(), golden.end());
            REQUIRE(words == golden);
        }

        WHEN("Search string is 'basstec'") {
            CharMap chars("basstec");
            auto words = dict.findWords(chars, options);
            StringVector golden = {"caste", "cast", "bast",
                                   "bass",  "cat",  "bat"};
            std::sort(words.begin(), words.end());
            std::sort(golden.begin(), golden.end());
            REQUIRE(words == golden);
        }
    }
}

SCENARIO("Checking if it's a word") {
    GIVEN("A list of words") {
        bananas::DictionaryFindOptions options;
        options.dictionary_file = bananas::resolvePath("tests/test_words.txt");
        Dictionary dict(options);

        WHEN("Search string is 'bar'") { REQUIRE(dict.isWord("bar") == true); }

        WHEN("Search string is 'bareyl'") {
            REQUIRE(dict.isWord("bareyl") == false);
        }

        WHEN("Search string is 'ba'") { REQUIRE(dict.isWord("ba") == false); }
    }
}

SCENARIO("Length pass") {
    GIVEN("A list of words") {
        bananas::DictionaryFindOptions options;
        options.dictionary_file = bananas::resolvePath("tests/test_words.txt");
        Dictionary dict(options);

        WHEN("Must be more than or equal to four characters") {
            CharMap chars("abder");
            DictionaryFindOptions options;
            options.length_range = {4, -1};
            auto words = dict.findWords(chars, options);
            StringVector golden = {"bare", "bard"};
            std::sort(words.begin(), words.end());
            std::sort(golden.begin(), golden.end());
            REQUIRE(words == golden);
        }

        WHEN("Must be less than four characters") {
            CharMap chars("basstec");
            DictionaryFindOptions options;
            options.length_range = {-1, 3};
            auto words = dict.findWords(chars, options);
            StringVector golden = {"cat", "bat"};
            std::sort(words.begin(), words.end());
            std::sort(golden.begin(), golden.end());
            REQUIRE(words == golden);
        }

        WHEN("Must be between 4 and 5 characters") {
            CharMap chars("casterbai");
            DictionaryFindOptions options;
            options.length_range = {4, 5};
            auto words = dict.findWords(chars, options);
            StringVector golden = {"cast", "caste", "bast", "bare"};
            std::sort(words.begin(), words.end());
            std::sort(golden.begin(), golden.end());
            REQUIRE(words == golden);
        }
    }
}

}  // namespace bananas
