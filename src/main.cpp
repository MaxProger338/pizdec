#include <iostream>

// #include "components/DB/UserDB/UserDB.h"

#include "modules/DB/DB.h"
#include "modules/DB/struct/Aliases/AliasRules.h"
#include "modules/DB/struct/Aliases/custom/String/Rules/StringAliasRules.h"
#include "modules/DB/struct/Aliases/custom/String/Rules/ChooseAliasRules.h"

std::vector<char>
    _concat(
        const std::vector<char>& vec1, 
        const std::vector<char>& vec2
    ) 
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
    std::vector<char> _englishAlphabetLowercase {
        'a','b','c','d','e','f','g','h',
        'i','j','k','l','m','n','o','p',
        'q','r','s','t','u','v','w','x',
        'y','z'
    };

    std::vector<char> _englishAlphabetUppercase {
        'A','B','C','D','E','F','G','H','I',
        'J','K','L','M','N','O','P','Q','R',
        'S','T','U','V','W','X','Y','Z'
    };

    std::vector<char> _numbers {
        '0','1','2','3','4','5','6','7','8','9' 
    };

    std::vector<char> _orderSymbols {
        '!','@','#','$','%','^','&',
        '*','(',')','?'
    };

    std::vector<char> _englishAlphabet                   { _concat(_englishAlphabetLowercase, _englishAlphabetUppercase) };

    std::vector<char> _uppercaseEnglishAlphabetAndNumbers{ _concat(_englishAlphabetUppercase, _numbers) };

    std::vector<char> _validSymbolsWithoutOrderSymbols   { _concat(_englishAlphabet, _numbers) };

    std::vector<char> _validSymbolsWithOrderSymbols      { _concat(_validSymbolsWithoutOrderSymbols, _orderSymbols) };

    //  std::map<std::string, Aliases::AliasRules*> _cols;

    // _cols["login"] = new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols);
    // _cols["password"] = new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols);
    // _cols["uuid"] = new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols);

    // DBs::DB db("data/users/users.txt", "~", _cols);
    
    std::vector<DBs::AliasAndHisName> cols;

    cols.push_back(
        DBs::AliasAndHisName{
            "login", 
            new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols)
        }
    );
    cols.push_back(
        DBs::AliasAndHisName{
            "password",
            new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols)
        }
    );
    cols.push_back(
        DBs::AliasAndHisName{
            "uuid",
            new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols)
        }
    );
    cols.push_back(
        DBs::AliasAndHisName(
            "is_admin",
            new Aliases::ChooseAliasRules(std::vector<std::string>{"yes", "no"})
        )
    );

    try
    {
        // DBs::UserDB db;

        // Users::User* user = db.auth("MaxProger338", "47855337CC6A988E672E74BBD0CEAAB7");

        // std::cout << user->uuid << '\n';

        // delete user;

        // DB connect
        DBs::DB db(
            "data/users/users.txt",
            "~",
            cols
        );
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
        delete i.alias;
    }

    return 0;
}