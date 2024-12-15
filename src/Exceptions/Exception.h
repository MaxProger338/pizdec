#pragma once

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

namespace Exceptions
{
    class Exception
    {
        protected:
            std::string _msgCustom;

        public:
            Exception(): 
                Exception("") {}

            Exception(std::string msg):
                _msgCustom{ msg } {}

            virtual std::string what() const = 0;
    };
};

#endif