#pragma once

#define ADMIN_KEY "123456"

#include "../DB/WrapperDB/WrapperDB.h"
#include "../../modules/Crypto/MD5/MD5.h"

#include <iostream>
#include <string>

namespace Model
{
    class Model
    {
        private:
            static void print(const char* str)
            {
                std::cout << str;
            }

            static void printGreen(const char* str)
            {
                std::cout << "\033[32;1m" << str << "\033[0m";
            }

            static void printRed(const char* str)
            {
                std::cout << "\033[31;1m" << str << "\033[0m";
            }

            static void printPurple(const char* str)
            {
                std::cout << "\u001b[35;1m" << str << "\033[0m";
            }

            static void printBlack(const char* str)
            {
                std::cout << "\u001b[30m;1m" << str << "\033[0m";
            }

            static void printYellow(const char* str)
            {
                std::cout << "\u001b[33;1m" << str << "\033[0m";
            }

            static void printBlue(const char* str)
            {
                std::cout << "\u001b[36;1m" << str << "\033[0m";
            }

            static void printRedBlue(const char* str)
            {
                std::cout << "\u001b[34;1m" << str << "\033[0m";
            }

            static void print(const std::string str)
            {
                const char* strChar = str.c_str();

                print(strChar);
            }

            static void printGreen(const std::string str)
            {
                const char* strChar = str.c_str();

                printGreen(strChar);
            }

            static void printRed(const std::string str)
            {
                const char* strChar = str.c_str();

                printRed(strChar);
            }

            static void printPurple(const std::string str)
            {
                const char* strChar = str.c_str();

                printPurple(strChar);
            }

            static void printBlack(const std::string& str)
            {
                const char* strChar = str.c_str();

                printBlack(strChar);
            }

            static void printYellow(const std::string& str)
            {
                const char* strChar = str.c_str();

                printYellow(strChar);
            }

            static void printBlue(const std::string& str)
            {
                const char* strChar = str.c_str();

                printBlue(strChar);
            }

            static void printRedBlue(const std::string& str)
            {
                const char* strChar = str.c_str();

                printRedBlue(strChar);
            }

            static Users::User* _auth()
            {
                while (true)
                {
                    std::string login;
                    std::string password;
                    std::string passwordHash;

                    print("\n");
                    print("Enter login: ");
                    std::cin >> login;

                    print("\n");
                    print("Enter password: ");
                    std::cin >> password;

                    passwordHash = Crypto::MD5::hash(password);

                    print("\n");

                    try
                    {
                        Users::User* user = DBs::WrapperDB::auth(login, passwordHash);

                        printPurple("You are Welcome, ");
                        printPurple(user->getName());
                        printPurple("!\n\n");

                        return user;
                    }
                    catch(const std::exception& e)
                    {
                        printRed(e.what());
                        print("\n");
                    }
                }
            }

            static Users::User* _reg()
            {
                while (true)
                {
                    std::string login;
                    std::string password;
                    std::string passwordHash;
                    std::string name;
                    std::string address;
                    std::string phone;

                    char isAdmin    = 'n';
                    bool isContinue = false;

                    if (isContinue == false)
                    {
                        while (true)
                    {
                        print("\n");
                        printBlue("Your regist as Admin? (y/n) ");
                        std::cin >> isAdmin;

                        if (isAdmin == 'y' || isAdmin == 'n')
                        {
                            if (isAdmin == 'y')
                            {
                                std::string adminKey;

                                print("\n");
                                printBlue("Enter secret key: ");
                                std::cin >> adminKey;

                                if (adminKey != ADMIN_KEY)
                                {
                                    print("\n");
                                    printRed("Keys are not valid\n");
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    }

                    isContinue =  true;

                    print("\n");
                    print("Enter login: ");
                    std::cin >> login;

                    print("\n");
                    print("Enter password: ");
                    std::cin >> password;

                    print("\n");
                    print("Enter your name: ");
                    std::cin >> name;

                    print("\n");
                    print("Enter your home address: ");
                    std::cin >> address;

                    print("\n");
                    print("Enter your phone: ");
                    std::cin >> phone;

                    // ------ Данные получены, теперь создаём пользоватедя ------

                    passwordHash = Crypto::MD5::hash(password);

                    print("\n");

                    DBs::AccountsDBData accountData;

                    // Hash uuid
                    time_t myTime        = time(NULL);

                    accountData.uuid     = Crypto::MD5::hash(std::to_string(myTime));

                    printRed(login);
                    printRed("\n");
                    printRed(password);
                    printRed("\n");
                    printRed(name);
                    printRed("\n");
                    printRed(address);
                    printRed("\n");
                    printRed(phone);
                    printRed("\n");
                    printRed(passwordHash);
                    printRed("\n");
                    printRed(accountData.uuid);
                    printRed("\n");
                    printRed(isAdmin == 'y' ? "yes" : "no");
                    printRed("\n");

                    // ------ Сама регистрация ------

                    if (isAdmin == 'y')
                    {
                        printRed("Regist as Admin!\n");

                        accountData.is_admin = "yes";

                        DBs::AdminsDataDBData adminsDataDBData;

                        adminsDataDBData.name    = name;
                        adminsDataDBData.address = address;
                        adminsDataDBData.phone   = phone;

                        try
                        {
                            Users::Admin* admin = DBs::WrapperDB::regAdmin(
                                login, 
                                passwordHash,
                                accountData,
                                adminsDataDBData
                            );

                            printPurple("Welcome, ");
                            printPurple(admin->getName());
                            printPurple("!\n\n");

                            return admin;
                        }
                        catch(const std::exception& e)
                        {
                            printRed(e.what());
                            print("\n");
                        }
                    }
                    else
                    {
                        printRed("Regist as Testable!\n");

                        accountData.is_admin = "no";

                        DBs::UsersDataDBData userDataDBData;

                        userDataDBData.name    = name;
                        userDataDBData.address = address;
                        userDataDBData.phone   = phone;

                        try
                        {
                            Users::Testable* testable = DBs::WrapperDB::regTestable(
                                login, 
                                passwordHash,
                                accountData,
                                userDataDBData
                            );

                            printPurple("Hello, ");
                            printPurple(testable->getName());
                            printPurple("!\n\n");

                            return testable;
                        }
                        catch(const std::exception& e)
                        {
                            printRed(e.what());
                            print("\n");
                        }
                    }
                }

                return nullptr;
            }

            static Users::User* _firstPar()
            {
                printPurple("Hello!\n\n");

                printYellow("0 - exit (in future)\n\n\n");

                printYellow("==========================================\n");

                Users::User* user = nullptr;
                while (true)
                {
                    printGreen("\nRegist - 1 / Auth - 2: ");
                    
                    short regOrAuth = 0;

                    std::cin >> regOrAuth;

                    switch (regOrAuth)
                    {
                        case 1:
                            printYellow("------------ ");
                            printYellow("Regist");
                            printYellow(" ------------\n");

                            user = _reg();

                            return user;

                        case 2:
                            printYellow("------------ ");
                            printYellow("Auth");
                            printYellow(" ------------\n");

                            user = _auth();

                            return user;

                        case 0:
                            printPurple("\nBye!\n\n");
                            return nullptr;
                    
                        default:
                            printRed("There number are not exists\n");
                            break;
                    }
                }

                return user;
            }

        public:
            static void process()
            {
                Users::User* user = nullptr;

                user = _firstPar();

                if (user == nullptr)
                {
                    return;
                }

                printYellow("------------ ");
                printYellow("Work");
                printYellow(" ------------\n");

                printRedBlue(user->getName());
                print("\n");
                printRedBlue(user->getAddress());
                print("\n");
                printRedBlue(user->getPhone());
                print("\n");

                while (true)
                {

                }

                delete user;
            }
    };
};
