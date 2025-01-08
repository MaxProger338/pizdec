#define CONFIG_DATA_PATH "data/users/users.txt"

#define CONFIG_DB_IN_ROW_SEPARATOR "~"

#include "modules/DB/DB.h"

#include "modules/DB/struct/Aliases/AliasRules.h"
#include "modules/DB/struct/Aliases/custom/String/Rules/StringAliasRules.h"

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

std::vector<char> concat(const std::vector<char>& vec1, const std::vector<char>& vec2)
{
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

int main(int argc, char** argv)
{
    std::vector<char> englishAlphabetLowercase {
        'a','b','c','d','e','f','g','h',
        'i','j','k','l','m','n','o','p',
        'q','r','s','t','u','v','w','x',
        'y','z'
    };

    std::vector<char> englishAlphabetUppercase {
        'A','B','C','D','E','F','G','H','I',
        'J','K','L','M','N','O','P','Q','R',
        'S','T','U','V','W','X','Y','Z'
    };

    std::vector<char> numbers {
        '0','1','2','3','4','5','6','7','8','9' 
    };

    std::vector<char> orderSymbols {
        '!','@','#','$','%','^','&',
        '*','(',')','?'
    };

    std::vector<char> englishAlphabet{ concat(englishAlphabetLowercase, englishAlphabetUppercase) };

    std::vector<char> uppercaseEnglishAlphabetAndNumbers{ concat(englishAlphabetUppercase, numbers) };

    std::vector<char> validSymbolsWithoutOrderSymbols{ concat(englishAlphabet, numbers) };

    std::vector<char> validSymbolsWithOrderSymbols{ concat(validSymbolsWithoutOrderSymbols, orderSymbols) };

    std::map<std::string, Aliases::AliasRules*> cols;

    cols["name"]     = new Aliases::StringAliasRules(validSymbolsWithoutOrderSymbols);
    cols["password"] = new Aliases::StringAliasRules(uppercaseEnglishAlphabetAndNumbers);
    cols["uuid"]     = new Aliases::StringAliasRules(uppercaseEnglishAlphabetAndNumbers);

    try
    {
        // DB connect
        DBs::DB db(
            CONFIG_DATA_PATH,
            CONFIG_DB_IN_ROW_SEPARATOR,
            cols
        );

        // Getting data from db
        std::vector <std::map<std::string, std::string> > datas { 
            db[0],
        };

        for (auto i : datas)
        {
            for (auto j : i)
            {
                std::cout << j.first << ": " << j.second << '\n';
            }
            std::cout << '\n';
        }
    } 
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "FUCK YOU!!! (said by MEMORY)" << '\n';
    }

    for (auto i : cols)
    {
        delete i.second;
    }

    return 0;
}