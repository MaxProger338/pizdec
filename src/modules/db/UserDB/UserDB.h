#pragma once 

#ifndef __USER_DATA_BASE_H__
#define __USER_DATA_BASE_H__

#include "../../../Exceptions/FileExceptions/FileNotFound/FileNotFound.h"
#include "../../Crypto/MD5/MD5.h"

#include "../../../components/Users/Testable/Testable.h"

#include <string>
#include <fstream>

typedef unsigned short ushort;

namespace DBs
{
    class UserDB final
    {
        private:
            std::string _path;

            static bool _isExistsFile(std::string path);

            static bool _isCorrectFile(std::string path);

        public: 
            UserDB(std::string path);

            bool reg(std::string login, std::string password, const Users::User& user) const;
    };
};

#include "UserDB.cpp"

#endif