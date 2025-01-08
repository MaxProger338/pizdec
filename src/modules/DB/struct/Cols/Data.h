#pragma once

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <set>

namespace DBTools
{
    class Data
    {
        private:
            std::map<std::string, std::string> _cols;

            bool _isExistsReplays(std::vector<std::string> cols) const
            {
                return std::set<std::string>( cols.begin(), cols.end() ).size() != cols.size();
            }

            std::vector<std::string> mapToVec(std::map<std::string, std::string> map)
            {
                std::vector<std::string> vec;

                for (auto i : map)
                {
                    vec.push_back(i.first);
                }
                
                return vec;
            }

        public:
            Data(std::vector<std::string> cols)
            {
                if (_isExistsReplays(cols))
                {
                    throw std::runtime_error("Columns are duplicated!");
                }
            }

            std::string get(std::string col);

            void update(std::string col, std::string val);
    };
};