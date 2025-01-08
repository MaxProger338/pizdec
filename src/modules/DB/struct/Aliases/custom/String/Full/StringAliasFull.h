#pragma once

#include "../../../AliasFull.h"

#include <vector>

namespace Aliases
{
    class StringAliasFull : public AliasFull
    {
        protected:
            std::vector<char> _symbols;

        public:
            StringAliasFull(std::string data, std::vector<char> symbols): 
                AliasFull(data), _symbols{ symbols } 
            {
                setData(data);
            }

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