#pragma once

#ifndef __ADMIN_H__
#define __ADMIN_H__

#include "../User/User.h"

namespace Users
{
    class Admin : virtual public User
    {
        protected:

        public:
    };
};

#include "Admin.cpp";

#endif