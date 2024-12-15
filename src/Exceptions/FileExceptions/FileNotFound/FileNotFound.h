#pragma once

#ifndef __FILE_NOT_FOUND_H__
#define __FILE_NOT_FOUND_H__

#include "../FileExceptins.h"

#include <string>

namespace Exceptions
{
    class FileNotFound : virtual public FileException
    {
        protected:
            std::string error = "File Not Found: ";

        public:
            FileNotFound(std::string fileName):
                FileException(fileName) {}

            FileNotFound(std::string fileName, std::string msg): 
                FileException(msg, fileName) {}

            std::string what() const override
            {
                std::string exceptionFinal = "Exception: ";
                
                exceptionFinal += _exceptionMsg;

                exceptionFinal += error;

                exceptionFinal += _fileName;

                exceptionFinal += '\n';
                exceptionFinal += "Message: ";
                exceptionFinal += _msgCustom;

                return exceptionFinal;    
            }
    };
};

#endif