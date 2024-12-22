#include "modules/db/UserDB/UserDB.h"

#include "Exceptions/Exception.h"

#include "components/Users/User/User.h"

#include <iostream>

using namespace DBs;

int main(int argc, char** argv)
{
    try
    {
        UserDB usersDB("H:/pizdec/src/data/users/users.txt");

        usersDB.reg("maxproger338@maiol.ru", "arduPyj338", Users::Testable("MaxProger338", 5));
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