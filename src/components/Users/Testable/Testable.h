#pragma once

#ifndef __USER_H__
#define __USER_H__

#include "../User/User.h"

namespace Users
{
    class Testable : public User
    {
        protected:

        public:
            Testable(std::string name, age age):
                User(name, age) {}
    };
};

#endif