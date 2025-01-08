#pragma once

#include "Alias.h"

#include <string>
#include <iostream>
#include <exception>

namespace Aliases
{
    class AliasFull : public Alias
    {
        protected:
            virtual bool _isValid(std::string str) const override = 0;

        public:
            AliasFull(std::string data): 
                Alias(data) {}

            bool isValid() const
            {
                return _isValid(*_data);
            }
    };
};