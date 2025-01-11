#pragma once 

#define CONFIG_ACCOUNTS_DB_PATH "data/accounts/accounts.txt"

#define CONFIG_ACCOUNTS_DB_IN_ROW_SEPARATOR "~"

#include "../../../modules/DB/DB.h"
#include "../../../modules/DB/struct/Aliases/AliasRules.h"
#include "../../../modules/DB/struct/Aliases/custom/String/Rules/StringAliasRules.h"
#include "../../../modules/DB/struct/Aliases/custom/String/Rules/ChooseAliasRules.h"

#include "../../../data/SymbolsArrays.h"

#include <string>
#include <vector>
#include <iostream>

namespace DBs
{
    struct AccountsDBData
    {
        std::string  uuid;
        std::string  is_admin;
    };

    class AccountsDB final
    {
        private:
            enum ERROR_STATUS
            {
                SUCCESS,
                USER_ALREADY_EXISTS,
            };

            std::vector<DBs::AliasAndHisName> _cols;

            DBs::DB*                          _db;

            void destruct                ()
                                            noexcept;

            std::string _getErrorMsgByStatus (
                                                ERROR_STATUS error
                                             ) const noexcept;

            // Get
            AccountsDBData _get          (
                                            const DB&          db,
                                            const std::string& login, 
                                            const std::string& password
                                         ) const;

            AccountsDBData _getImpl      (
                                            const DB&          db,
                                            const std::string& login, 
                                            const std::string& password
                                         ) const noexcept;

            // Is exists
            bool           _isExists     (
                                            const DB&          db,
                                            const std::string& login, 
                                            const std::string& password
                                         ) const;

            bool           _isExistsImpl (
                                            const DB&          db,
                                            const std::string& login, 
                                            const std::string& password
                                         ) const noexcept;

            // Add
            void           _add          (
                                            DBs::DB&              db, 
                                            const std::string&    login,
                                            const std::string&    password,
                                            const AccountsDBData& usersData
                                         );

            ERROR_STATUS   _checkIsAdded (
                                            DBs::DB&              db, 
                                            const std::string&    login,
                                            const std::string&    password,
                                            const AccountsDBData& usersData
                                         ) noexcept;

            void           _addImpl      (
                                            DBs::DB&              db, 
                                            const std::string&    login,
                                            const std::string&    password,
                                            const AccountsDBData& usersData
                                         ) noexcept;

        public: 
            AccountsDB          ();

            ~AccountsDB         ();

            AccountsDBData get  (
                                    const std::string& login, 
                                    const std::string& password
                                ) const;

            bool     isExists   (
                                    const std::string& login, 
                                    const std::string& password
                                ) const;

            void     add        (
                                    const std::string&    login,
                                    const std::string&    password,
                                    const AccountsDBData& usersData
                                );
    };
};
