#pragma once

#include "../AccountsDB/AccountsDB.h"
#include "../UsersDataDB/UsersDataDB.h"
#include "../AdminsDataDB/AdminsDataDB.h"

#include "../../Users/User/User.h"
#include "../../Users/Testable/Testable.h"
#include "../../Users/Admin/Admin.h"

#include <string>

namespace DBs
{
    class WrapperDB final 
    {
        private:
            enum ERROR_STATUS
            {
                SUCCESS,
                ACCOUNT_ALREADY_EXISTS,
                USERDATA_ALREADY_EXISTS,
                ACCOUNTS_DATA_INVALID,
                USERS_DATA_INVALID,
            };

            static std::string _getErrorMsgByStatus (
                                                        ERROR_STATUS error
                                                    ) noexcept;

            // Auth
            static Users::User*     _auth           (
                                                        const std::string& login, 
                                                        const std::string& password
                                                    );

            static Users::Testable* _authTestable     (
                                            const std::string& login, 
                                            const std::string& password
                                          );

            static Users::Admin* _authAdmin (
                                            const std::string& login, 
                                            const std::string& password
                                           );

            static Users::Testable* _authTestableImpl (
                                            const AccountsDB&  accountsDB,
                                            const UsersDataDB& usersDataDB,
                                            const std::string& login, 
                                            const std::string& password
                                          ) noexcept;

            static Users::Admin* _authAdminImpl (
                                            const AccountsDB&   accountsDB,
                                            const AdminsDataDB& adminsDataDB,
                                            const std::string&  login, 
                                            const std::string&  password
                                          ) noexcept;

            // Reg
            static Users::Testable* _regTestable      (
                                            const std::string&      login, 
                                            const std::string&      password,
                                            const AccountsDBData&   accountData,
                                            const UsersDataDBData&  userData
                                          );

            static Users::Admin* _regAdmin      (
                                            const std::string&      login, 
                                            const std::string&      password,
                                            const AccountsDBData&   accountData,
                                            const AdminsDataDBData& adminData
                                          );

            static Users::Testable* _regTestableImpl (
                                            AccountsDB&             accountsDB,
                                            UsersDataDB&            usersDataDB,
                                            const std::string&      login, 
                                            const std::string&      password,
                                            const AccountsDBData&   accountData,
                                            const UsersDataDBData&  userData
                                          ) noexcept;

            static Users::Admin* _regAdminImpl (
                                                AccountsDB&             accountsDB,
                                                AdminsDataDB&           adminsDataDB,
                                                const std::string&      login, 
                                                const std::string&      password,
                                                const AccountsDBData&   accountData,
                                                const AdminsDataDBData& adminData
                                              ) noexcept;

        public:
            static Users::Testable* authTestable (
                                            const std::string& login, 
                                            const std::string& password
                                          );

            static Users::Admin* authAdmin (
                                            const std::string& login, 
                                            const std::string& password
                                          );

            static Users::User* auth     (
                                            const std::string& login, 
                                            const std::string& password
                                          );

            static Users::Testable* regTestable       (
                                            const std::string&      login, 
                                            const std::string&      password,
                                            const AccountsDBData&   accountData,
                                            const UsersDataDBData&  userData
                                          );

            static Users::Admin* regAdmin  (
                                            const std::string&      login, 
                                            const std::string&      password,
                                            const AccountsDBData&   accountData,
                                            const AdminsDataDBData& adminData
                                          );
    };
};
