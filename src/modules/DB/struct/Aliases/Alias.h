#pragma once

#include <string>
#include <iostream>
#include <exception>

namespace Aliases
{
    class Alias
    {
        protected:
            std::string* _data;
            
            Alias& clearData()
            {
                delete _data;
                _data = nullptr;

                return *this;
            }
            
            virtual bool _isValid(std::string str) const = 0;

        public:
            Alias(): 
                _data{ nullptr } {}

            Alias(std::string data): 
                _data{ new std::string(data) } {}

            virtual ~Alias()
            {
                clearData();
            }

            Alias& setData(std::string newData)
            {
                if (!_isValid(newData))
                {
                    throw std::runtime_error("New data is invalid!");
                }

                clearData();
                _data = new std::string(newData);

                return *this;
            }

            std::string* getData() const
            {
                if (!_isValid(*_data))
                {
                    throw std::runtime_error("Data is invalid!");
                }
                
                return _data;
            }
    };
};
