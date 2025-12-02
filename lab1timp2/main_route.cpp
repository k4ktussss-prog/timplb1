#include <iostream>
#include <string>
#include <locale>
#include "routeCipher.h"

using namespace std;

int main()
{
    locale::global(locale("ru_RU.utf8"));
    wcout.imbue(locale());

    int columns;
    int mode;
    wstring text;

    wcout << L"Введите количество столбцов: ";
    wcin >> columns;
    wcin.ignore(); 

    wcout << L"Введите текст: ";
    getline(wcin, text);

    wcout << L"Выберите режим (1 - шифровать, 2 - расшифровать): ";
    wcin >> mode;

    routeCipher cipher(columns);

    if (mode == 1) {
        wstring encrypted = cipher.encrypt(text);
        wcout << L"Зашифрованный текст: " << encrypted << endl;
    } else if (mode == 2) {
        wstring decrypted = cipher.decrypt(text);
        wcout << L"Расшифрованный текст: " << decrypted << endl;
    } else {
        wcout << L"Неверный режим" << endl;
    }

    return 0;
}

