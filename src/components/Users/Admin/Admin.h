#pragma once

#ifndef __ADMIN_H__
#define __ADMIN_H__

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

#endif