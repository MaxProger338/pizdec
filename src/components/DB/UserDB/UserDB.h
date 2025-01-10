#pragma once 

#define CONFIG_DATA_PATH "data/users/users.txt"

#define CONFIG_DB_IN_ROW_SEPARATOR "~"

#include "../../../modules/DB/DB.h"
#include "../../../modules/DB/struct/Aliases/AliasRules.h"
#include "../../../modules/DB/struct/Aliases/custom/String/Rules/StringAliasRules.h"
#include "../../../modules/DB/struct/Aliases/custom/String/Rules/ChooseAliasRules.h"

#include "../../../modules/Crypto/MD5/MD5.h"
#include "../../../components/Users/Testable/Testable.h"
#include "../../../components/Users/Admin/Admin.h"

#include <string>
#include <vector>
#include <iostream>

namespace DBs
{
    class UserDB final
    {
        private:
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

            // std::map<std::string, Aliases::AliasRules*> _cols;

            // DBs::DB _db;

            std::vector<char> _concat                            (
                                                                    const std::vector<char>& vec1, 
                                                                    const std::vector<char>& vec2
                                                                 ) const;

            // // Auth
            // Users::User* _auth                                  (
            //                                                         const DB&   db,
            //                                                         std::string login, 
            //                                                         std::string password
            //                                                     ) const;

            // Users::User* _authImpl                              (
            //                                                         const DB&   db,
            //                                                         std::string login, 
            //                                                         std::string password
            //                                                     ) const noexcept;

        public: 
            UserDB ();

            ~UserDB();

            // Users::User* auth                                   (
            //                                                         std::string login, 
            //                                                         std::string password
            //                                                     ) const;
    };
};
