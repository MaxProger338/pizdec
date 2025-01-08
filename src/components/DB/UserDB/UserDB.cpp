#include "UserDB.h"

using namespace DBs;
using namespace PlukiPlukiLib;

UserDB::
    UserDB(std::string path):
        _connect{ new PlukiPluki(path, std::ios::in) } {}

UserDB::
    ~UserDB()
    {
        delete _connect;
        _connect = nullptr;
    }

std::vector<std::string> UserDB::
    _parseDB() const
    {
        std::vector<std::string> parseUsers{ _connect->indexAllFile() };

        
    }

bool UserDB::
    _isCorrectDBView() const
    {
        if (_connect->getMode() != std::ios::in)
        {
            _connect->reopen(std::ios::in);
        }

        __amountRows amountUsers = _connect->getAmountRows();
        if (amountUsers < 2)
        {
            return false;
        }

        if ((*_connect)[0] != DB_BEGIN)
        {
            return false;
        }

        if ((*_connect)[amountUsers - 1] != DB_END)
        {
            return false;
        }

        return true;
    }

bool UserDB::
    reg(std::string login, std::string password, const Users::User& user) const
    {
        std::cout << _isCorrectDBView() << '\n';

        return true;
    }