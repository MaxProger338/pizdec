#pragma once

namespace Users
{
    typedef unsigned short age;

    class User
    {
        protected:
            std::string _name;
            std::string _address;
            std::string _phone;

        public:
            User(std::string name, std::string address, std::string phone):
                _name{ name }, _address{ address }, _phone{ phone } {}

            virtual std::string getName() const = 0;

            virtual std::string getAddress() const = 0;

            virtual std::string getPhone() const = 0;
    };
};