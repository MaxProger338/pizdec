#include "SymbolsArrays.h"

using namespace Data;

std::vector<char> SymbolsArrays::
    _concat(
        const std::vector<char>& vec1, 
        const std::vector<char>& vec2
    ) {
        unsigned int size = vec1.size() + vec2.size();

        std::vector<char> res(size);

        for (size_t i = 0; i < vec1.size() + vec2.size(); i++)
        {
            if (i < vec1.size())
            {
                res[i] = vec1[i];
            }
            else
            {
                res[i] = vec2[i - vec1.size()];
            }
        }    

        return res;
    }

std::vector<char> SymbolsArrays::englishAlphabetLowercase 
{
    'a','b','c','d','e','f','g','h',
    'i','j','k','l','m','n','o','p',
    'q','r','s','t','u','v','w','x',
    'y','z'
};

std::vector<char> SymbolsArrays::englishAlphabetUppercase 
{
    'A','B','C','D','E','F','G','H','I',
    'J','K','L','M','N','O','P','Q','R',
    'S','T','U','V','W','X','Y','Z'
};

std::vector<char> SymbolsArrays::numbers 
{
    '0','1','2','3','4','5','6','7','8','9'
};

std::vector<char> SymbolsArrays::orderSymbols 
{
    '!','@','#','$','%','^','&',
    '*','(',')','?'
};

std::vector<char> SymbolsArrays::englishAlphabet 
{
    _concat(englishAlphabetLowercase, englishAlphabetUppercase)
};

std::vector<char> SymbolsArrays::uppercaseEnglishAlphabetAndNumbers 
{ 
    _concat(englishAlphabetUppercase, numbers)
};

std::vector<char> SymbolsArrays::lowercaseEnglishAlphabetAndNumbers
{
    _concat(englishAlphabetLowercase, numbers)
};

std::vector<char> SymbolsArrays::validSymbolsWithoutOrderSymbols 
{
    _concat(englishAlphabet, numbers)
};

std::vector<char> SymbolsArrays::validSymbolsWithOrderSymbols 
{
    _concat(_concat(englishAlphabet, numbers), orderSymbols)
};

std::vector<char> SymbolsArrays::englishAlphabetAndSpace 
{
    _concat(englishAlphabet, std::vector<char>{'`'})
};

std::vector<char> SymbolsArrays::validSymbolsWithoutOrderSymbolsandSpace 
{
    _concat(validSymbolsWithoutOrderSymbols, std::vector<char>{'`'})
};