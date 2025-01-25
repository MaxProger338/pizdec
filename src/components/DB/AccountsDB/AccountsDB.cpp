#include "AccountsDB.h"

using namespace DBs;

AccountsDB::
    AccountsDB():
        _cols {
            DBs::AliasAndHisName(
                "login", 
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::validSymbolsWithoutOrderSymbols
                )
            ),
            DBs::AliasAndHisName(
                "password",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::uppercaseEnglishAlphabetAndNumbers
                )
            ),
            DBs::AliasAndHisName(
                "uuid",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::uppercaseEnglishAlphabetAndNumbers
                )
            ),
            DBs::AliasAndHisName(
                "is_admin",
                new Aliases::ChooseAliasRules(std::vector<std::string>{"yes", "no"})
            )
        }
    {
        // TODO: Подумай!
        try
        {
            _db = new DBs::DB(CONFIG_ACCOUNTS_DB_PATH, CONFIG_ACCOUNTS_DB_IN_ROW_SEPARATOR, _cols);
        }
        catch(const std::exception& e)
        {
            destruct();
            throw std::runtime_error(e.what());
        }
        catch(...)
        {
            destruct();
            throw std::runtime_error("Error!");
        }
    }

AccountsDB::
    ~AccountsDB()
    {
        destruct();
    }

void AccountsDB::
    destruct() noexcept
    {
        for (auto i : _cols)
        {
            delete i.alias;
        }

        delete _db;
    }

std::string AccountsDB::
    _getErrorMsgByStatus(ERROR_STATUS error) const noexcept
    {
        switch (error)
        {
            // case SUCCESS - должно проверяться перед вызовом функции!
            case USER_ALREADY_EXISTS: return "User already exists!";     

            default:                  return "Unknow file error!";
        }
    }

// Get

AccountsDBData AccountsDB::
    _get (
        const DB&          db,
        const std::string& login, 
        const std::string& password
    ) const
    {
        if (!_isExists(db, login, password))
        {
            throw std::runtime_error("User not found!");
        }

        return _getImpl(db, login, password);
    }

AccountsDBData AccountsDB::
    _getImpl(
        const DB&          db,
        const std::string& login, 
        const std::string& password
    ) const noexcept
    {
        __amountRowsInDB amountRows = db.getAmountRows();

        __amountRowsInDB foundUserIndex = 0;
        for (size_t i = 0; i < amountRows; i++)
        {
            __responseData data = db.getRow(i);

            if (data["login"] == login && data["password"] == password)
            {
                foundUserIndex = i;
                break;
            }
        }

        AccountsDBData userData;

        __responseData foundUser = db.getRow(foundUserIndex);

        userData.uuid     = foundUser["uuid"];
        userData.is_admin = foundUser["is_admin"];

        return userData;
    }

// End Get

// Is exists
bool AccountsDB::
    _isExists (
        const DB&          db,
        const std::string& login, 
        const std::string& password
    ) const
    {
        return _isExistsImpl(db, login, password);
    }

bool AccountsDB::
    _isExistsImpl (
        const DB&          db,
        const std::string& login, 
        const std::string& password
    ) const noexcept
    {
        __amountRowsInDB amountRows = db.getAmountRows();

        for (size_t i = 0; i < amountRows; i++)
        {
            __responseData data = db.getRow(i);

            // TODO: || data["password"] == password
            if (data["login"] == login)
            {
                return true;
            }
        }

        return false;
    }

// End Is Exists

// Add
void AccountsDB::
    _add (
        DBs::DB&              db, 
        const std::string&    login,
        const std::string&    password, 
        const AccountsDBData& usersData
    ) {
        ERROR_STATUS addErrorStatus = _checkIsAdded(db, login, password, usersData);

        if (addErrorStatus != SUCCESS)
        {
            throw std::runtime_error(_getErrorMsgByStatus(addErrorStatus));
        }
    }

AccountsDB::ERROR_STATUS AccountsDB::
    _checkIsAdded (
        DBs::DB&              db, 
        const std::string&    login,
        const std::string&    password, 
        const AccountsDBData& usersData
    ) noexcept
    {
        if (_isExistsImpl(db, login, password))
        {
            return USER_ALREADY_EXISTS;
        }

        _addImpl(db, login, password, usersData);

        return SUCCESS;
    }

void AccountsDB::
    _addImpl (
        DBs::DB&              db, 
        const std::string&    login,
        const std::string&    password, 
        const AccountsDBData& usersData
    ) noexcept
    {
        std::vector<std::string> vec;

        vec.push_back(login);
        vec.push_back(password);
        vec.push_back(usersData.uuid);
        vec.push_back(usersData.is_admin);

        db.addRow(vec);
    }

// End Add

bool AccountsDB::
    _isValidData  (
        const std::string&    login,
        const std::string&    password,
        const AccountsDBData& accountsData
    ) const noexcept
    {
        __stringVec vec;

        vec.push_back(login);
        vec.push_back(password);
        vec.push_back(accountsData.uuid);
        vec.push_back(accountsData.is_admin);

        return _db->isValidData(vec);
    }

AccountsDBData AccountsDB::
    get (
        const std::string& login, 
        const std::string& password
    ) const
    {
        return _get(*_db, login, password);
    }

bool AccountsDB::
    isExists (
        const std::string& login, 
        const std::string& password
    ) const
    {
        return _isExists(*_db, login, password);
    }

void AccountsDB::
    add (
        const std::string&    login,
        const std::string&    password,
        const AccountsDBData& usersData
    ) {
        _add(*_db, login, password, usersData);
    }

bool AccountsDB::
    isValidData  (
        const std::string&    login,
        const std::string&    password,
        const AccountsDBData& accountsData
    ) const noexcept
    {
        return _isValidData(login, password, accountsData);
    }