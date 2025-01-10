#pragma once

#include "../../../AliasFull.h"

#include <vector>
#include <string>

namespace Aliases
{
    class ChooseAliasFull : public AliasFull
    {
        protected:
            std::vector<std::string> _choose;

        public:
            ChooseAliasFull(std::string data, std::vector<std::string> choose): 
                AliasFull(data), _choose{ choose } 
            {
                setData(data);
            }

            bool _isValid(std::string str) const override
            {
                for (auto i : _choose)
                {
                    if (str == i)
                    {
                        return true;
                    }
                }
                
                return true;
            }
    };
};