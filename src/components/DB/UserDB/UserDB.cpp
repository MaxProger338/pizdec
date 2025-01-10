#include "UserDB.h"

using namespace DBs;

UserDB::
    UserDB()
        // _db { CONFIG_DATA_PATH, CONFIG_DB_IN_ROW_SEPARATOR, _cols },

        // _cols {
        //     {"login",    new Aliases::StringAliasRules(_validSymbolsWithoutOrderSymbols)}, 
        //     {"password", new Aliases::StringAliasRules(_uppercaseEnglishAlphabetAndNumbers)},
        //     {"uuid",     new Aliases::StringAliasRules(_uppercaseEnglishAlphabetAndNumbers)},
        //     {"is_admin", new Aliases::ChooseAliasRules(std::vector<std::string>{"yes", "no"})}
        // }
    {
        // std::cout << _cols.size();
        // _db{ CONFIG_DATA_PATH, CONFIG_DB_IN_ROW_SEPARATOR, _cols };
    }

UserDB::
    ~UserDB()
    {
        // for (auto i : _cols)
        // {
        //     delete i.second;
        // }
    }

std::vector<char> UserDB::
    _concat(
        const std::vector<char>& vec1, 
        const std::vector<char>& vec2
    ) const
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

// // Auth

// Users::User* UserDB::
//     _auth (
//         const DB&   db,
//         std::string login, 
//         std::string password
//     ) const
//     {
//         return _authImpl(db, login, password);
//     }

// Users::User* UserDB::
//     _authImpl(
//         const DB&   db,
//         std::string login, 
//         std::string password
//     ) const noexcept
//     {
//         __amountRowsInDB amountRows = db.getAmountRows();

//         __amountRowsInDB foundUserIndex = 0;
//         for (size_t i = 0; i < amountRows; i++)
//         {
//             __responseData data = db.getRow(i);

//             if (data["login"] == login && data["password"] == password)
//             {
//                 foundUserIndex = i;
//                 break;
//             }
//         }

//         __responseData foundUser = db.getRow(foundUserIndex);

//         if (foundUser["is_admin"] == "yes")
//         {
//             Users::Admin* admin = new Users::Admin("name", 28);
//             admin->uuid = foundUser["uuid"];

//             return admin;
//         }
//         else
//         {
//             Users::Testable* testable = new Users::Testable("name", 28);
//             testable->uuid = foundUser["uuid"];

//             return testable;
//         }
//     }

// // End Auth

// Users::User* UserDB::
//     auth (
//         std::string login, 
//         std::string password
//     ) const
//     {
//         return _auth(_db, login, password);
//     }