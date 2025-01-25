#include "AdminsDataDB.h"

using namespace DBs;

AdminsDataDB::
    AdminsDataDB():
        _cols {
            DBs::AliasAndHisName (
                "uuid", 
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::uppercaseEnglishAlphabetAndNumbers
                )
            ),
            DBs::AliasAndHisName (
                "name",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::englishAlphabetAndSpace
                )
            ),
            DBs::AliasAndHisName (
                "address",
                new Aliases::StringAliasRules (
                    Data::SymbolsArrays::validSymbolsWithoutOrderSymbolsAndSpace
                )
            ),
            DBs::AliasAndHisName (
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
            _db = new DBs::DB(CONFIG_ADMINS_DATA_DB_PATH, CONFIG_ADMINS_DATA_DB_IN_ROW_SEPARATOR, _cols);
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

AdminsDataDB::
    ~AdminsDataDB()
    {
        _destruct();
    }

void AdminsDataDB::
    _destruct() noexcept
    {
        for (auto i : _cols)
        {
            delete i.alias;
        }

        delete _db;
    }

std::string AdminsDataDB::
    _getErrorMsgByStatus(ERROR_STATUS error) const noexcept
    {
        switch (error)
        {
            // case SUCCESS - должно проверяться перед вызовом функции!

            default:                      return "Unknow file error!";
        }
    }

// Get row
AdminsDataDBData AdminsDataDB::
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

AdminsDataDBData AdminsDataDB::
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

        AdminsDataDBData usersDataDBData;

        __responseData foundUser = db.getRow(foundUserIndex);

        usersDataDBData.name    = foundUser["name"];
        usersDataDBData.address = foundUser["address"];
        usersDataDBData.phone   = foundUser["phone"];

        return usersDataDBData;
    }

// End Get row

// Is row exists

bool AdminsDataDB::
    _isExists (
        const DBs::DB&     db, 
        const std::string& uuid
    ) const
    {
        return _isExistsImpl(db, uuid);
    }

bool AdminsDataDB::
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
void AdminsDataDB::
    _add (
        DBs::DB&                db, 
        const std::string&      uuid,
        const AdminsDataDBData& usersData
    ) {
        ERROR_STATUS addErrorStatus = _checkIsAdded(db, uuid, usersData);

        if (addErrorStatus != SUCCESS)
        {
            throw std::runtime_error(_getErrorMsgByStatus(addErrorStatus));
        }
    }

AdminsDataDB::ERROR_STATUS AdminsDataDB::
    _checkIsAdded (
        DBs::DB&                db, 
        const std::string&      uuid,
        const AdminsDataDBData& usersData
    ) noexcept 
    {
        _addImpl(db, uuid, usersData);

        return SUCCESS;
    }

void AdminsDataDB::
    _addImpl (
        DBs::DB&                db, 
        const std::string&      uuid,
        const AdminsDataDBData& usersData
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

bool AdminsDataDB::
    _isValidData  (
        const std::string&      uuid,
        const AdminsDataDBData& usersData
    ) const noexcept
    {
        __stringVec vec;

        vec.push_back(uuid);
        vec.push_back(usersData.name);
        vec.push_back(usersData.address);
        vec.push_back(usersData.phone);

        return _db->isValidData(vec);
    }

AdminsDataDBData AdminsDataDB::
    get(std::string uuid) const
    {
        return _get(*_db, uuid);
    }

bool AdminsDataDB::
    isExists(std::string uuid) const
    {
        return _isExists(*_db, uuid);
    }

void AdminsDataDB::
    add(
        const std::string&      uuid,
        const AdminsDataDBData& usersData
    ) {
        _add(*_db, uuid, usersData);
    }


bool AdminsDataDB::
    isValidData (
        const std::string&      uuid,
        const AdminsDataDBData& usersData
    ) const noexcept
    {
        return _isValidData(uuid, usersData);
    }