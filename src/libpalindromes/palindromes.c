#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int len_file(FILE* text)
{
    int size = 0;
    wchar_t symb;
    while ((symb = fgetwc(text)) != EOF) {
        size++;
    }
    return size;
}

wchar_t* init_wchar(int size)
{
    wchar_t* point = malloc(sizeof(wchar_t) * (size));
    if (!point) {
        return (0);
    } else {
        return point;
    }
}

int len_str(wchar_t* sentence)
{
    int i = 0;
    while (sentence[i] != '\0') {
        i++;
    }
    return (i + 1);
}

void wchar_strcpy(wchar_t* sentence, wchar_t* sec_sentence)
{
    int i;
    for (i = 0; sentence[i] != '\0'; i++) {
        sec_sentence[i] = sentence[i];
    }
    sec_sentence[i] = '\0';
}

void wchar_tolower(wchar_t* sentence)
{
    int i = 0;
    while (sentence[i] != '\0') {
        if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
            sentence[i] += 32;
        }
        if (sentence[i] >= 1040 && sentence[i] <= 1071) {
            sentence[i] += 32;
        } // 1040 - 'А', 1071 - 'Я' (UTF-8)
        i++;
    }
}

wchar_t* wchar_strcat(wchar_t* dest, const wchar_t* src)
{
    wchar_t* tmp = dest;

    while (*dest)
        dest++;
    while ((*dest++ = *src++) != '\0')
        ;
    return tmp;
}

void wchar_delsymb(wchar_t* sentence, int size, char ch)
{
    int i, j, k = 0;
    while (k < size) {
        i = 0;
        j = 0;
        while (i < size) {
            if (sentence[i] == ch) {
                sentence[i] = sentence[i + 1];
                for (j = i; j < size; j++) {
                    sentence[j] = sentence[j + 1];
                }
            }
            i++;
        }
        k++;
    }
}

void clear(wchar_t* sentence, int size)
{
    char prip[] = {'"', ',', ';', ':', '!', '?', '(', ')', '-'};
    int i;

    for (i = 0; i < 9; i++) {
        wchar_delsymb(sentence, size, prip[i]);
    }
}

int* sent_sep(wchar_t* sentence, int* parts)
{
    int i = 0, count = 1;
    for (i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!'
            || sentence[i] == '\0') {
            count++;
        }
    }

    parts = malloc(sizeof(int) * (count + 1));
    parts[0] = count;
    count = 0;
    int num = 0;
    for (i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!'
            || sentence[i] == '\0') {
            if (count > 1) {
                parts[count + 1] = i - count + 1;
            } else {
                parts[count + 1] = i;
            }
            count++;
            num += count;
        }
        parts[count + 1] = i - count + 1;
    }
    return parts;
}

int cat_words(wchar_t* sentence, int start)
{
    int i = start;
    while (sentence[i] != '\0' && sentence[i] != ',' && sentence[i] != '!'
           && sentence[i] != '.' && sentence[i] != ' ' && sentence[i] != '?') {
        i++;
    }
    return i;
}

void copy_word(wchar_t* sentence, wchar_t* word, int start, int end)
{
    int i;
    for (i = 0; i < (end - start); i++) {
        word[i] = sentence[i + start];
    }
    word[i] = '\0';
}

int satisfactorily(wchar_t* sentence, int size)
{
    wchar_tolower(sentence);
    // wchar_delsymb(sentence, size, ' ');
    size = len_str(sentence);
    int flag = 1;
    int i;

    for (i = 0; i < (size / 2); i++) {
        if (sentence[i] != sentence[size - i - 2]) {
            flag = 0;
            break;
        }
    }
    if (i <= 1) {
        flag = 0;
    }
    return flag;
}

int find_palinroms(wchar_t* sentence, int size, wchar_t* palindroms)
{
    wchar_t* space = init_wchar(1);
    *space = ' ';
    wchar_t* buf_sentence = init_wchar(size);
    wchar_strcpy(sentence, buf_sentence);
    int start = 0, end, flag = 0;

    clear(buf_sentence, size);
    do {
        end = cat_words(buf_sentence, start);
        int size = end - start + 1;

        wchar_t* word;
        word = init_wchar(size);
        copy_word(buf_sentence, word, start, end);
        if (satisfactorily(word, (end - start)) == 1) {
            wchar_strcat(palindroms, space);
            wchar_strcat(palindroms, word);
            flag = 1;
        }

        start = end + 1;
    } while (buf_sentence[end] != '\0');
    return flag;
}

int good(wchar_t* sentence, int* parts, int size, wchar_t* palindroms)
{
    int flag = 0;
    wchar_t* new = L"\n     ";
    wchar_t* buf_part;

    clear(sentence, size);

    parts = sent_sep(sentence, parts);
    wchar_delsymb(sentence, size, '.');
    int i = 0;
    int j = 0;
    for (i = 1; i < parts[0] + 1; i++) {
        if (j != parts[parts[0]]) {
            buf_part = init_wchar((parts[i] - j + 1));
            copy_word(sentence, buf_part, j, parts[i]);
            wchar_delsymb(buf_part, parts[i] - j + 1, ' ');
            if (satisfactorily(buf_part, parts[i]) == 1) {
                if (flag == 1) {
                    wchar_strcat(palindroms, new);
                }
                wchar_strcat(palindroms, buf_part);
                flag = 1;
            }

            j = parts[i];
        }
    }
    return flag;
}
