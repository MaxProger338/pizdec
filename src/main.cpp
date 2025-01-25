#include <iostream>

#include "components/Model/Model.h"

int main(int argc, char** argv)
{
    try
    {
        // std::vector<std::string> splitStr;

        // std::istringstream stream("gfrgreg~rgerger rgerg~gf");
        // std::string token;

        // while (std::getline(stream, token, '~')) 
        // {
        //     splitStr.push_back(token);
        // }

        // for (auto i : splitStr)
        // {
        //     std::cout << i << '\n';
        // }

        Model::Model::process();
    } 
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "FUCK YOU!!! (said by MEMORY)" << '\n';
    }

    return 0;
}