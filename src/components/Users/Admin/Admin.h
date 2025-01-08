#pragma once

#include "../User/User.h"

namespace Users
{
    class Admin : public User
    {
        protected:

        public:
            Admin(std::string name, age age):
                User(name, age) {}
    };
};