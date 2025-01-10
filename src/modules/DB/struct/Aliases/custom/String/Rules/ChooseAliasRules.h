#pragma once

#include "../../../AliasRules.h"

#include <vector>
#include <string>

namespace Aliases
{
    class ChooseAliasRules : public AliasRules
    {
        protected:
            std::vector<std::string> _choose;

        public:
            ChooseAliasRules(std::vector<std::string> choose): 
                AliasRules(), _choose{ choose } {}

            bool _isValid(std::string str) const override
            {
                for (auto i : _choose)
                {
                    if (str == i)
                    {
                        return true;
                    }
                }
                
                return false;
            }
    };
};