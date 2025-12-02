#pragma once
#include <vector>
#include <string>

class routeCipher
{
private:
    int columns;

    std::wstring prepareText(const std::wstring& text);
    std::vector<std::vector<wchar_t>> createTable(const std::wstring& text, int cols);
    std::wstring readEncrypted(const std::vector<std::vector<wchar_t>>& table, int cols);
    std::wstring readDecrypted(const std::vector<std::vector<wchar_t>>& table, int cols);

public:
    routeCipher() = delete;
    routeCipher(int cols);

    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
};
