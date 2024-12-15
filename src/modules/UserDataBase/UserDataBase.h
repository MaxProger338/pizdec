#pragma once 

#ifndef __USER_DATA_BASE_H__
#define __USER_DATA_BASE_H__

#include "../../Exceptions/FileExceptions/FileNotFound/FileNotFound.h"

#include <string>
#include <fstream>

namespace UserDataBase
{
    class UserDataBase
    {
        private:
            std::string _path;

            static bool _isExistsFile(std::string path)
            {
                std::ifstream file(path);

                if (!file.is_open())
                {
                    return false;
                }

                file.close();

                return true;
            }

        public: 
            UserDataBase(std::string path):
                _path{ path } 
            {
                if (!_isExistsFile(path))
                {
                    throw Exceptions::FileNotFound(path);
                }
            }

            
    };
};

#include "UserDataBase.cpp"

#endif