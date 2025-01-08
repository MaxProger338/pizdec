#pragma once

#include "Alias.h"

#include <string>
#include <iostream>
#include <exception>

namespace Aliases
{
    class AliasRules : public Alias
    {
        protected:
            virtual bool _isValid(std::string str) const override = 0;

        public:
            AliasRules(): 
                Alias() {}

            bool isValid(std::string data) const
            {
                return _isValid(data);
            }
    };
};