#include "modules/UserDataBase/UserDataBase.h"

#include "Exceptions/Exception.h"

#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        UserDataBase::UserDataBase db("H:/pizdec/src/data/users/users.txt");
    }
    catch(const Exceptions::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cout << "FUCK YOU!!! (said by MEMORY)" << '\n';
    }

    return 0;
}