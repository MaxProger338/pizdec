#pragma once

#ifndef __FILE_EXCEPTIONS_H__
#define __FILE_EXCEPTIONS_H__

#include "../Exception.h"

#include <string>

namespace Exceptions
{
    class FileException : public Exception
    {
        protected:
            std::string _exceptionMsg = "File Error: ";
            std::string _fileName;

        public:
            FileException(std::string fileName):
                Exception(), _fileName{ fileName } {}

            FileException(std::string fileName, std::string msg): 
                Exception(msg), _fileName{ fileName } {}

            virtual std::string what() const override = 0;
    };
};

#endif