#ifndef GUARD_BANANAGRAMS_H
#define GUARD_BANANAGRAMS_H

struct DictionaryFindOptions_s {
    char* dictionary_file;
    unsigned int dictionary_file_len;

    float freq_min;
    float freq_max;
    int len_min;
    int len_max;
};
typedef struct DictionaryFindOptions_s DictionaryFindOptions;
extern const DictionaryFindOptions DictionaryFindOptions_default;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

extern char* c_play(DictionaryFindOptions* options, char* chars,
                    unsigned int char_num, int time_constraint, int* num_tiles);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // GUARD_BANANAGRAMS_H
