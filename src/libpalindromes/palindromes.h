#pragma once
#include <stddef.h>
#include <stdio.h>

int len_file(FILE* text);
wchar_t* init_wchar(int size);
int len_str(wchar_t* sentence);
void wchar_strcpy(wchar_t* sentence, wchar_t* sec_sentence);
void wchar_tolower(wchar_t* sentence);
wchar_t* wchar_strcat(wchar_t* dest, const wchar_t* src);
void wchar_delsymb(wchar_t* sentence, int size, char ch);
void clear(wchar_t* sentence, int size);
int* sent_sep(wchar_t* sentence, int* parts);
int cat_words(wchar_t* sentence, int start);
void copy_word(wchar_t* sentence, wchar_t* word, int start, int end);
int satisfactorily(wchar_t* sentence, int size);
int find_palinroms(wchar_t* sentence, int size, wchar_t* palindroms);
int good(wchar_t* sentence, int* parts, int size, wchar_t* palindroms);
