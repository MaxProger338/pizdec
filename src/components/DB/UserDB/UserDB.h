#pragma once 

// #define DB_BEGIN "USERS:"
// #define DB_END   "END"

#include "../../Crypto/MD5/MD5.h"

#include "../../../components/Users/Testable/Testable.h"

#include "../../../Libs/PlukiPluki-Lib/include/PlukiPluki.h"

#include <string>
#include <vector>

namespace DBs
{
    class UserDB final
    {
        private:
            PlukiPlukiLib::PlukiPluki* _connect;

            bool _isCorrectDBView() const;

            std::vector<std::string> _parseDB() const;

        public: 
            UserDB(std::string path);

            ~UserDB();

            bool reg(std::string login, std::string password, const Users::User& user) const;
    };
};
