#ifndef GUARD_BANANAGRAMS_H
#define GUARD_BANANAGRAMS_H

struct DictionaryFindOptions {
    char* dictionary_file;
    unsigned int dictionary_file_len;

    float freq_min = 0;
    float freq_max = 0;
    int len_min = 0;
    int len_max = 0;
};
typedef struct DictionaryFindOptions DictionaryFindOptions;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

extern char* c_play(DictionaryFindOptions* options, char* chars,
                    unsigned int char_num, int time_constraint, int& num_tiles);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // GUARD_BANANAGRAMS_H
