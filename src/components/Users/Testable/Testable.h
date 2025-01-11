#pragma once

#include "../User/User.h"

#include <string>

namespace Users
{
    class Testable : public User
    {
        public:
            Testable(std::string name, std::string address, std::string phone):
                User(name, address, phone) {}

            std::string getName() const override
            {
                return _name;
            }

            std::string getAddress() const override
            {
                return _address;
            }

            std::string getPhone() const override
            {
                return _phone;
            }
    };
};