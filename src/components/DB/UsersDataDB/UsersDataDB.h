#pragma once 

#define CONFIG_USERS_DATA_DB_PATH "data/users_data/users_data.txt"

#define CONFIG_USERS_DATA_DB_IN_ROW_SEPARATOR "~"

#include "../../../modules/DB/DB.h"
#include "../../../modules/DB/struct/Aliases/AliasRules.h"
#include "../../../modules/DB/struct/Aliases/custom/String/Rules/StringAliasRules.h"

#include "../../../data/SymbolsArrays.h"

#include <string>
#include <vector>
#include <iostream>

namespace DBs
{
    struct UsersDataDBData
    {
        std::string name;
        std::string address;
        std::string phone;
    };
    
    class UsersDataDB final
    {
        private:
            enum ERROR_STATUS
            {
                SUCCESS,
            };

            std::vector<DBs::AliasAndHisName> _cols;

            DBs::DB*                          _db;

            void           _destruct      ()
                                            noexcept;

            std::string _getErrorMsgByStatus (
                                                ERROR_STATUS error
                                             ) const noexcept;

            // Get 
            UsersDataDBData _get          (
                                            const DBs::DB&     db,
                                            const std::string& uuid
                                          ) const;

            UsersDataDBData _getImpl      (
                                            const DBs::DB&     db, 
                                            const std::string& uuid
                                          ) const noexcept;

            // Is row exists
            bool           _isExists     (
                                            const DBs::DB&     db, 
                                            const std::string& uuid
                                         ) const;

            bool           _isExistsImpl (
                                            const DBs::DB&     db, 
                                            const std::string& uuid
                                         ) const noexcept;

            // Add
            void           _add          (
                                            DBs::DB&               db, 
                                            const std::string&     uuid,
                                            const UsersDataDBData& usersData
                                         );

            ERROR_STATUS   _checkIsAdded (
                                            DBs::DB&               db, 
                                            const std::string&     uuid,
                                            const UsersDataDBData& usersData
                                         ) noexcept;

            void           _addImpl      (
                                            DBs::DB&               db, 
                                            const std::string&     uuid,
                                            const UsersDataDBData& usersData
                                         ) noexcept;


        public: 
            UsersDataDB             ();

            ~UsersDataDB            ();

            UsersDataDBData get     (std::string uuid)
                                        const;

            bool           isExists (std::string uuid)
                                        const;

            void           add      (
                                        const std::string&     uuid,
                                        const UsersDataDBData& usersData
                                    );
    };
};
