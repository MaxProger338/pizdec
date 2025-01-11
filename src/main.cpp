#include <iostream>

#include "components/Model/Model.h"

int main(int argc, char** argv)
{
    try
    {
        setlocale(LC_ALL, "");

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