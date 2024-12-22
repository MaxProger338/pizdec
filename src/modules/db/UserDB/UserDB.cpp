#include "UserDB.h"

using namespace DBs;

inline UserDB::
    UserDB(std::string path):
        _path{ path } 
    {
        if (!_isExistsFile(path))
        {
            throw Exceptions::FileNotFound(path);
        }
    }

inline bool UserDB::_isExistsFile(std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    file.close();

    return true;
}

inline bool UserDB::_isCorrectFile(std::string path)
{
    if (_isExistsFile(path))
    {
        std::fstream file(path);

        if (!file.is_open())
        {
            return false;
        }

        ushort number = 0;
        std::string str;
        while (!file.eof()) 
        {
            file >> str;
            std::cout << str << '\n';
        }

        file.close();

        return true;
    }

    return false;
}

inline bool UserDB::
    reg(std::string login, std::string password, const Users::User& user) const
    {
        _isCorrectFile(_path);

        return true;
    }