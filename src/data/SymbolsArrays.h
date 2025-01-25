#pragma once

#include <vector>

namespace Data
{
    class SymbolsArrays
    {
        private:
            static std::vector<char> _concat (
                const std::vector<char>& vec1, 
                const std::vector<char>& vec2
            );

        public:
            static std::vector<char> englishAlphabetLowercase;

            static std::vector<char> englishAlphabetUppercase;

            static std::vector<char> numbers;

            static std::vector<char> orderSymbols;

            static std::vector<char> englishAlphabet;

            static std::vector<char> uppercaseEnglishAlphabetAndNumbers;

            static std::vector<char> lowercaseEnglishAlphabetAndNumbers;

            static std::vector<char> validSymbolsWithoutOrderSymbols;

            static std::vector<char> validSymbolsWithOrderSymbols;

            static std::vector<char> englishAlphabetAndSpace;

            static std::vector<char> validSymbolsWithoutOrderSymbolsAndSpace;
    };
};