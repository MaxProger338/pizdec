#include "WrapperDB.h"

using namespace DBs;

std::string WrapperDB::
    _getErrorMsgByStatus(ERROR_STATUS error) noexcept
    {
        switch (error)
        {
            // case SUCCESS - должно проверяться перед вызовом функции!
            case ACCOUNT_ALREADY_EXISTS:  return "Account already exists!";
            case USERDATA_ALREADY_EXISTS: return "UserData already exists!";
            case ACCOUNTS_DATA_INVALID:   return "Accounts Data invalid!";
            case USERS_DATA_INVALID:      return "Users Data invalid!";

            default:                      return "Unknow file error!";
        }
    }

// Auth
Users::User* WrapperDB::
    _auth (
        const std::string& login, 
        const std::string& password
    ) {
        AccountsDB accountsDB;

        if (!accountsDB.isExists(login, password))
        {
            throw std::runtime_error("Uncorrect login / password!");
        }

        AccountsDBData  userData        = accountsDB.get(login, password);

        std::string     uuid            = userData.uuid;

        std::string     is_admin        = userData.is_admin;

        if (is_admin == "yes")
        {
            AdminsDataDB     adminsDataDB;

            if (!adminsDataDB.isExists(uuid))
            {
                throw std::runtime_error("Uncorrect uuid!");
            }

            return _authAdmin(login, password);
        }
        else
        {
            UsersDataDB     usersDataDB;

            if (!usersDataDB.isExists(uuid))
            {
                throw std::runtime_error("Uncorrect uuid!");
            }

            return _authTestable(login, password);
        }
    }

Users::Testable* WrapperDB::
    _authTestable (
        const std::string& login, 
        const std::string& password
    ) {
        AccountsDB accountsDB;

        if (!accountsDB.isExists(login, password))
        {
            throw std::runtime_error("Uncorrect login / password!");
        }

        AccountsDBData  userData        = accountsDB.get(login, password);

        std::string     uuid            = userData.uuid;

        std::string     is_admin        = userData.is_admin;

        UsersDataDB     usersDataDB;

        if (!usersDataDB.isExists(uuid))
        {
            throw std::runtime_error("Uncorrect uuid!");
        }

        if (is_admin != "no")
        {
            throw std::runtime_error("This user is not testable!");
        }

        return _authTestableImpl(accountsDB, usersDataDB, login, password);
    }

Users::Admin* WrapperDB::
    _authAdmin (
        const std::string& login, 
        const std::string& password
    ) {
        AccountsDB accountsDB;

        if (!accountsDB.isExists(login, password))
        {
            throw std::runtime_error("Uncorrect login / password!");
        }

        AccountsDBData  userData        = accountsDB.get(login, password);

        std::string     uuid            = userData.uuid;

        std::string     is_admin        = userData.is_admin;

        AdminsDataDB    adminsDataDB;

        if (!adminsDataDB.isExists(uuid))
        {
            throw std::runtime_error("Uncorrect uuid!");
        }

        if (is_admin != "yes")
        {
            throw std::runtime_error("This user is not admin!");
        }

        return _authAdminImpl(accountsDB, adminsDataDB, login, password);
    }

Users::Testable* WrapperDB::
    _authTestableImpl (
        const AccountsDB&   accountsDB,
        const UsersDataDB&  usersDataDB,
        const std::string&  login, 
        const std::string&  password
    ) noexcept
    {
        AccountsDBData  userData        = accountsDB.get(login, password);

        std::string     uuid            = userData.uuid;

        UsersDataDBData usersDataDBData = usersDataDB.get(uuid);

        Users::Testable* user = nullptr;

        std::string name    = usersDataDBData.name;
        std::string address = usersDataDBData.address;
        std::string phone   = usersDataDBData.phone;

        user = new Users::Testable(name, address, phone);

        return user;
    }

Users::Admin* WrapperDB::
    _authAdminImpl (
        const AccountsDB&   accountsDB,
        const AdminsDataDB& adminsDataDB,
        const std::string&  login, 
        const std::string&  password
    ) noexcept
    {
        AccountsDBData  userData         = accountsDB.get(login, password);

        std::string     uuid             = userData.uuid;

        AdminsDataDBData adminsDataDBData = adminsDataDB.get(uuid);

        Users::Admin* user = nullptr;

        std::string name    = adminsDataDBData.name;
        std::string address = adminsDataDBData.address;
        std::string phone   = adminsDataDBData.phone;

        user = new Users::Admin(name, address, phone);

        return user;
    }

// End Auth

// Reg
Users::Testable* WrapperDB::
    _regTestable (
        const std::string&      login, 
        const std::string&      password,
        const AccountsDBData&   accountData,
        const UsersDataDBData&  userData
    ) {
        AccountsDB accountsDB;

        if (!accountsDB.isValidData(login, password, accountData))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ACCOUNTS_DATA_INVALID));
        }

        if (accountsDB.isExists(login, password))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ACCOUNT_ALREADY_EXISTS));
        }

        UsersDataDB userDataDB;

        std::string uuid = accountData.uuid;

        if (!userDataDB.isValidData(uuid, userData))
        {
            throw std::runtime_error(_getErrorMsgByStatus(USERS_DATA_INVALID));
        }

        if (userDataDB.isExists(uuid))
        {
            throw std::runtime_error(_getErrorMsgByStatus(USERDATA_ALREADY_EXISTS));
        }

        return _regTestableImpl(accountsDB, userDataDB, login, password, accountData, userData);
    }

Users::Admin* WrapperDB::
    _regAdmin (
        const std::string&      login, 
        const std::string&      password,
        const AccountsDBData&   accountData,
        const AdminsDataDBData& adminData
    ) {
        AccountsDB accountsDB;
        
        if (accountsDB.isExists(login, password))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ACCOUNT_ALREADY_EXISTS));
        }

        AdminsDataDB adminDataDB;

        std::string uuid = accountData.uuid;

        if (adminDataDB.isExists(uuid))
        {
            throw std::runtime_error(_getErrorMsgByStatus(USERDATA_ALREADY_EXISTS));
        }

        return _regAdminImpl(accountsDB, adminDataDB, login, password, accountData, adminData);
    }

Users::Testable* WrapperDB::
    _regTestableImpl (
        AccountsDB&             accountsDB,
        UsersDataDB&            usersDataDB,
        const std::string&      login, 
        const std::string&      password,
        const AccountsDBData&   accountData,
        const UsersDataDBData&  userData
    ) noexcept {
        accountsDB.add(login, password, accountData);

        std::string uuid     = accountData.uuid;

        usersDataDB.add(uuid, userData);

        return _authTestableImpl(accountsDB, usersDataDB, login, password);
    }

Users::Admin* WrapperDB::
    _regAdminImpl (
        AccountsDB&             accountsDB,
        AdminsDataDB&           adminsDataDB,
        const std::string&      login, 
        const std::string&      password,
        const AccountsDBData&   accountData,
        const AdminsDataDBData& adminData
    ) noexcept {
        accountsDB.add(login, password, accountData);

        std::string uuid     = accountData.uuid;

        adminsDataDB.add(uuid, adminData);

        return _authAdminImpl(accountsDB, adminsDataDB, login, password);
    }

// End Reg

Users::User* WrapperDB::
    auth (
        const std::string& login, 
        const std::string& password
    ) {
        return _auth(login, password);
    }

Users::Testable* WrapperDB::
    authTestable (
        const std::string& login, 
        const std::string& password
    ) {
        return _authTestable(login, password);
    }

Users::Admin* WrapperDB::
    authAdmin (
        const std::string& login, 
        const std::string& password
    ) {
        return _authAdmin(login, password);
    }

Users::Testable* WrapperDB::
    regTestable (
        const std::string&     login, 
        const std::string&     password,
        const AccountsDBData&  accountData,
        const UsersDataDBData& userData
    ) {
        return _regTestable(login, password, accountData, userData);
    }

Users::Admin* WrapperDB::
    regAdmin (
        const std::string&      login, 
        const std::string&      password,
        const AccountsDBData&   accountData,
        const AdminsDataDBData& adminData
    ) {
        return _regAdmin(login, password, accountData, adminData);
    }