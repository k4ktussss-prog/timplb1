#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

using namespace std;

std::wstring string_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wstring_to_string(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

void check_ru(const wstring& text, const wstring& key)
{
    modAlphaCipher cipher(key);
    wstring encrypted = cipher.encrypt(text);
    wstring decrypted = cipher.decrypt(encrypted);

    wcout << L"Ключ: " << key << endl;
    wcout << L"Текст: " << text << endl;
    wcout << L"Зашифровано: " << encrypted << endl;
    wcout << L"Расшифровано: " << decrypted << endl;

    wstring text_no_spaces, decrypted_no_spaces;
    for (wchar_t c : text) if (c != L' ') text_no_spaces += c;
    for (wchar_t c : decrypted) if (c != L' ') decrypted_no_spaces += c;
    
    if (text_no_spaces == decrypted_no_spaces)
        wcout << L"УСПЕХ" << endl;
    else
        wcout << L"ОШИБКА" << endl;
    wcout << L"-------------------" << endl;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    check_ru(L"ПРИВЕТ", L"КЛЮЧ");
    check_ru(L"ПРОГРАММИРОВАНИЕ", L"ШИФР");
    check_ru(L"ТЕСТ", L"А");
    check_ru(L"ПРИВЕТ МИР", L"КЛЮЧ");
    check_ru(L"ЭТО ТЕКСТ С ПРОБЕЛАМИ", L"СЕКРЕТНЫЙКЛЮЧ"); 
    
    return 0;
}