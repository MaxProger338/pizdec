#include "UsersDataDB.h"

using namespace DBs;

UsersDataDB::
    UsersDataDB():
        _cols {
            DBs::AliasAndHisName(
                "uuid", 
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::uppercaseEnglishAlphabetAndNumbers
                )
            ),
            DBs::AliasAndHisName(
                "name",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::englishAlphabetAndSpace
                )
            ),
            DBs::AliasAndHisName(
                "address",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::validSymbolsWithoutOrderSymbols
                )
            ),
            DBs::AliasAndHisName(
                "phone",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::numbers
                )
            )
        }
    {
        // TODO: Подумай!
        try
        {
            _db = new DBs::DB(CONFIG_USERS_DATA_DB_PATH, CONFIG_USERS_DATA_DB_IN_ROW_SEPARATOR, _cols);
        }
        catch(const std::exception& e)
        {
            _destruct();
            throw std::runtime_error(e.what());
        }
        catch(...)
        {
            _destruct();
            throw std::runtime_error("Error!");
        }
    }

UsersDataDB::
    ~UsersDataDB()
    {
        _destruct();
    }

void UsersDataDB::
    _destruct() noexcept
    {
        for (auto i : _cols)
        {
            delete i.alias;
        }

        delete _db;
    }

std::string UsersDataDB::
    _getErrorMsgByStatus(ERROR_STATUS error) const noexcept
    {
        switch (error)
        {
            // case SUCCESS - должно проверяться перед вызовом функции!

            default:                      return "Unknow file error!";
        }
    }

// Get row
UsersDataDBData UsersDataDB::
    _get(
        const DBs::DB&     db,
        const std::string& uuid
    ) const
    {
        if (!_isExists(db, uuid))
        {
            throw std::runtime_error("Data not found!");
        }

        return _getImpl(db, uuid);
    }

UsersDataDBData UsersDataDB::
    _getImpl(
        const DBs::DB&    db,
        const std::string& uuid
    ) const noexcept
    {
        __amountRowsInDB amountRows = db.getAmountRows();

        __amountRowsInDB foundUserIndex = 0;
        for (__amountRowsInDB i = 0; i < amountRows; i++)
        {
            __responseData data = db.getRow(i);
            if (uuid == data["uuid"])
            {
                foundUserIndex = i;
                break;
            }
        }

        UsersDataDBData usersDataDBData;

        __responseData foundUser = db.getRow(foundUserIndex);

        usersDataDBData.name    = foundUser["name"];
        usersDataDBData.address = foundUser["address"];
        usersDataDBData.phone   = foundUser["phone"];

        return usersDataDBData;
    }

// End Get row

// Is row exists

bool UsersDataDB::
    _isExists (
        const DBs::DB&     db, 
        const std::string& uuid
    ) const
    {
        return _isExistsImpl(db, uuid);
    }

bool UsersDataDB::
    _isExistsImpl (
        const DBs::DB&     db, 
        const std::string& uuid
    ) const noexcept
    {
        __amountRowsInDB amountRows = db.getAmountRows();
        
        for (__amountRowsInDB i = 0; i < amountRows; i++)
        {
            __responseData data = db.getRow(i);
            if (uuid == data["uuid"])
            {
                return true;
            }
        }

        return false;
    }

// End Is row exists

// Add
void UsersDataDB::
    _add (
        DBs::DB&               db, 
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) {
        ERROR_STATUS addErrorStatus = _checkIsAdded(db, uuid, usersData);

        if (addErrorStatus != SUCCESS)
        {
            throw std::runtime_error(_getErrorMsgByStatus(addErrorStatus));
        }
    }

UsersDataDB::ERROR_STATUS UsersDataDB::
    _checkIsAdded (
        DBs::DB&               db, 
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) noexcept 
    {
        _addImpl(db, uuid, usersData);

        return SUCCESS;
    }

void UsersDataDB::
    _addImpl (
        DBs::DB&               db, 
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) noexcept
    {
        std::vector<std::string> vec;

        vec.push_back(uuid);
        vec.push_back(usersData.name);
        vec.push_back(usersData.address);
        vec.push_back(usersData.phone);

        db.addRow(vec);
    }

// End Add

bool UsersDataDB::
    _isValidData  (
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) const noexcept
    {
        __stringVec vec;

        vec.push_back(uuid);
        vec.push_back(usersData.name);
        vec.push_back(usersData.address);
        vec.push_back(usersData.phone);

        return _db->isValidData(vec);
    }

UsersDataDBData UsersDataDB::
    get(std::string uuid) const
    {
        return _get(*_db, uuid);
    }

bool UsersDataDB::
    isExists(std::string uuid) const
    {
        return _isExists(*_db, uuid);
    }

void UsersDataDB::
    add(
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) {
        _add(*_db, uuid, usersData);
    }

bool UsersDataDB::
    isValidData  (
        const std::string&     uuid,
        const UsersDataDBData& usersData
    ) const noexcept
    {
        return _isValidData(uuid, usersData);
    }