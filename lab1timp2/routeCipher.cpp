#include "routeCipher.h"
#include <algorithm>
#include <cctype>
#include <locale>

routeCipher::routeCipher(int cols) : columns(cols) {}

std::wstring toUpper(const std::wstring& text) {
    std::wstring result = text;
    std::locale loc("ru_RU.UTF-8");
    for (wchar_t& c : result) {
        c = std::toupper(c, loc);
    }
    return result;
}

std::wstring routeCipher::prepareText(const std::wstring& text)
{
    std::wstring result;
    std::wstring upperText = toUpper(text); // Сначала переводим в верхний регистр
    
    for (wchar_t c : upperText) {
        if (c != L' ') {
            result += c;
        }
    }
    return result;
}

std::vector<std::vector<wchar_t>> routeCipher::createTable(const std::wstring& text, int cols)
{
    int length = text.length();
    int rows = (length + cols - 1) / cols;
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(cols, L' '));

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < length) {
                table[i][j] = text[index++];
            }
        }
    }
    return table;
}

std::wstring routeCipher::readEncrypted(const std::vector<std::vector<wchar_t>>& table, int cols)
{
    int rows = table.size();
    std::wstring result;
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != L' ') {
                result += table[i][j];
            }
        }
    }
    return result;
}

std::wstring routeCipher::readDecrypted(const std::vector<std::vector<wchar_t>>& table, int cols)
{
    int rows = table.size();
    std::wstring result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (table[i][j] != L' ') {
                result += table[i][j];
            }
        }
    }
    return result;
}

std::wstring routeCipher::encrypt(const std::wstring& text)
{
    std::wstring prepared = prepareText(text);
    auto table = createTable(prepared, columns);
    return readEncrypted(table, columns);
}

std::wstring routeCipher::decrypt(const std::wstring& text)
{
    std::wstring prepared = prepareText(text);
    int length = prepared.length();
    int rows = (length + columns - 1) / columns;

    int extras = length % columns; 
    std::vector<int> heights(columns, rows);
    if (extras != 0) {
        for (int j = 0; j < columns; ++j) {
            heights[j] = (j < extras) ? rows : (rows - 1);
        }
    }

    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L' '));
    int index = 0;

    for (int j = columns - 1; j >= 0; j--) {
        int h = heights[j];
        for (int i = 0; i < h; i++) {
            if (index < length) {
                table[i][j] = prepared[index++];
            }
        }
    }
    return readDecrypted(table, columns);
}