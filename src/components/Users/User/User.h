#pragma once

#ifndef __TESTABLE_H__
#define __TESTABLE_H__

#include <string>

typedef unsigned short age;

typedef std::string email;

namespace Users
{
    class User
    {
        protected:
            std::string _name;
            age _age;

        public:
            User(std::string name, age age):
                _name{ name }, _age{ age } {}

            User& setName(const std::string& newName)
            {
                _name = newName;

                return *this;
            }

            std::string getName() const
            {
                return _name;
            }

            User& setAge(age newAge)
            {
                _age = newAge;

                return *this;
            }

            age getAge() const
            {
                return _age;
            }
    };
};

#endif