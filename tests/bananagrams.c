#include <stdio.h>
#include <stdlib.h>

#include "bananagrams/bananagrams.h"

int main() {
    DictionaryFindOptions options = DictionaryFindOptions_default;
    options.freq_min = 99;
    options.freq_max = 100;
    options.len_min = 3;
    options.len_max = -1;
    options.dictionary_file = "dictionaries/en_1.txt";
    options.dictionary_file_len = 22;

    char chars[39] = "aksdhfoweroweounsdkfnaweyuruewliuoiiioi";

    int num_tiles;
    char* board = c_play(&options, chars, 39, 0, &num_tiles);
    printf("%s", board);
    free(board);
}
