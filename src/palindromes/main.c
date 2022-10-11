#include "../libpalindromes/palindromes.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main(int argc, char** argv)
{
    (void)argc;
    setlocale(LC_ALL, "");

    FILE* text;
    text = fopen(argv[1], "r");

    int flag = 0;
    int size = 0;
    wchar_t* sentence;
    wchar_t* buf_sentence;
    wchar_t* palindroms;
    int* parts = NULL;

    size = len_file(text);
    size++;

    fseek(text, 0, SEEK_SET);

    sentence = init_wchar(size);
    buf_sentence = init_wchar(size);
    palindroms = init_wchar(size + 99);
    fgetws(sentence, size, text);
    wchar_strcpy(sentence, buf_sentence);

    //----- главное
    flag = find_palinroms(buf_sentence, size, palindroms);
    if (flag == 1) {
        wprintf(L"В тексте были найдены слова-палиндромы:%S\n", palindroms);
    } else {
        wprintf(L"В тексте нет слов-палиндромов.\n");
    }
    wprintf(L"-----\n");
    //----- удовл.
    flag = satisfactorily(buf_sentence, size);
    if (flag == 1) {
        wprintf(L"Весь текст входного файла целиком является палиндромом: ");
        wprintf(L"'%S'\n-----\n", sentence);
    } else {
        wprintf(L"Текст входного файла целиком НЕ является палиндромом "
                L"(учитывая пробелы и знаки препинания).\n-----\n");
    }
    //----- хорошо
    palindroms = init_wchar(size);
    flag = good(buf_sentence, parts, size, palindroms);
    if (flag == 1) {
        wprintf(L"В ведённом тексте палиндромами являютя следующие "
                L"предложения: \n     %S\n",
                palindroms);
    } else {
        wprintf(L"В тексте нет предложениий-палиндромов.\n");
    }
    wprintf(L"\nИсходное предложение: %S\n", sentence);
    fclose(text);
    free(sentence);
    free(palindroms);
    free(buf_sentence);
    free(parts);
    return 0;
}
