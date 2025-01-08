#pragma once

#include "../../../AliasRules.h"

#include <vector>

namespace Aliases
{
    class StringAliasRules : public AliasRules
    {
        protected:
            std::vector<char> _symbols;

        public:
            StringAliasRules(std::vector<char> symbols): 
                AliasRules(), _symbols{ symbols } {}

            bool _isValid(std::string str) const override
            {
                for (auto i : str)
                {
                    bool isIn = false;

                    for (auto j : _symbols)
                    {
                        if (i == j)
                        {
                            isIn = true;
                        }
                    }
                    
                    if (!isIn)
                    {
                        return false;
                    }
                }
                
                return true;
            }
    };
};