#pragma once

#define ADMIN_KEY "123456"

#include "../DB/WrapperDB/WrapperDB.h"
#include "../../modules/Crypto/MD5/MD5.h"

#include <iostream>

namespace Model
{
    class Model
    {
        private:
            static void print(const wchar_t* str)
            {
                std::wcout << str;
            }

            static void printGreen(const wchar_t* str)
            {
                std::wcout << "\033[32;1m" << str << "\033[0m";
            }

            static void printRed(const wchar_t* str)
            {
                std::wcout << "\033[31;1m" << str << "\033[0m";
            }

            static void printPurple(const wchar_t* str)
            {
                std::wcout << "\u001b[35;1m" << str << "\033[0m";
            }

            static void printBlack(const wchar_t* str)
            {
                std::wcout << "\u001b[30m;1m" << str << "\033[0m";
            }

            static void printYellow(const wchar_t* str)
            {
                std::wcout << "\u001b[33;1m" << str << "\033[0m";
            }

            static void printBlue(const wchar_t* str)
            {
                std::wcout << "\u001b[36;1m" << str << "\033[0m";
            }

            static void printRedBlue(const wchar_t* str)
            {
                std::wcout << "\u001b[34;1m" << str << "\033[0m";
            }

            static void print(const char* str)
            {
                std::wcout << str;
            }

            static void printGreen(const char* str)
            {
                std::wcout << "\033[32;1m" << str << "\033[0m";
            }

            static void printRed(const char* str)
            {
                std::wcout << "\033[31;1m" << str << "\033[0m";
            }

            static void printPurple(const char* str)
            {
                std::wcout << "\u001b[35;1m" << str << "\033[0m";
            }

            static void printBlack(const char* str)
            {
                std::wcout << "\u001b[30m;1m" << str << "\033[0m";
            }

            static void printYellow(const char* str)
            {
                std::wcout << "\u001b[33;1m" << str << "\033[0m";
            }

            static void printBlue(const char* str)
            {
                std::wcout << "\u001b[36;1m" << str << "\033[0m";
            }

            static void printRedBlue(const char* str)
            {
                std::wcout << "\u001b[34;1m" << str << "\033[0m";
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

                    print(L"\n");
                    print(L"Введите логин: ");
                    std::cin >> login;

                    print(L"\n");
                    print(L"Введите пароль: ");
                    std::cin >> password;

                    passwordHash = Crypto::MD5::hash(password);

                    print(L"\n");

                    try
                    {
                        Users::User* user = DBs::WrapperDB::auth(login, passwordHash);

                        printPurple(L"С возвращением, ");
                        printPurple(user->getName());
                        printPurple(L"!\n\n");

                        return user;
                    }
                    catch(const std::exception& e)
                    {
                        printRed(e.what());
                        print(L"\n");
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

                    char isAdmin = 'n';
                    bool isContinue = false;

                    print(L"\n");
                    printBlue(L"Вы регистрируетесь как Админ? (y/n) ");
                    std::cin >> isAdmin;

                    if (isAdmin == 'y' || isAdmin == 'n')
                    {
                        isContinue = true;
                    }

                    if (isContinue)
                    {
                        if (isAdmin == 'y')
                        {
                            std::string adminKey;

                            print(L"\n");
                            printBlue(L"Введите секретный ключ: ");
                            std::cin >> adminKey;

                            if (adminKey != ADMIN_KEY)
                            {
                                isContinue = false;

                                print(L"\n");
                                printRed(L"Ключи не совпадают\n");
                            }
                            else
                            {
                                // isAdmin = 'n';
                            }
                        }
                    }

                    if (isContinue)
                    {
                        print(L"\n");
                        print(L"Введите логин: ");
                        std::cin >> login;

                        print(L"\n");
                        print(L"Введите пароль: ");
                        std::cin >> password;

                        print(L"\n");
                        print(L"Введите ваше имя: ");
                        std::cin >> name;

                        print(L"\n");
                        print(L"Введите ваш домашний адрес: ");
                        std::cin >> address;

                        print(L"\n");
                        print(L"Введите ваш номер телефона: ");
                        std::cin >> phone;

                        passwordHash = Crypto::MD5::hash(password);

                        print(L"\n");

                        // ============== Сама регистрация ==============
                        DBs::AccountsDBData accountData;

                        // Hash uuid
                        time_t myTime        = time(NULL);

                        accountData.uuid     = Crypto::MD5::hash(std::to_string(myTime));

                        if (isAdmin == 'y')
                        {
                            try
                            {
                                accountData.is_admin = "yes";

                                DBs::AdminsDataDBData adminsDataDBData;

                                adminsDataDBData.name    = name;
                                adminsDataDBData.address = address;
                                adminsDataDBData.phone   = phone;

                                Users::Admin* admin = DBs::WrapperDB::regAdmin(
                                    login, 
                                    passwordHash,
                                    accountData,
                                    adminsDataDBData
                                );

                                printPurple(L"Добро пожаловать, ");
                                printPurple(admin->getName());
                                printPurple(L"!\n\n");

                                return admin;
                            }
                            catch(const std::exception& e)
                            {
                                printRed(e.what());
                                print(L"\n");
                            }
                        }
                        else if (isAdmin == 'n')
                        {
                            try
                            {
                                accountData.is_admin = "no";

                                DBs::UsersDataDBData userDataDBData;

                                userDataDBData.name    = name;
                                userDataDBData.address = address;
                                userDataDBData.phone   = phone;

                                Users::Testable* testable = DBs::WrapperDB::regTestable(
                                    login, 
                                    passwordHash,
                                    accountData,
                                    userDataDBData
                                );

                                printPurple(L"Приветствуем вас, ");
                                printPurple(testable->getName());
                                printPurple(L"!\n\n");

                                return testable;
                            }
                            catch(const std::exception& e)
                            {
                                printRed(e.what());
                                print(L"\n");
                            }
                        }
                    }
                }
            }

            static Users::User* _firstPar()
            {
                printPurple(L"Здравствуйте!\n\n");

                printYellow(L"0 - выход (в дальнейшем)\n\n\n");

                printYellow(L"==========================================\n");

                while (true)
                {
                    printGreen(L"\nРегистрация - 1 / Авторизация - 2: ");
                    
                    short regOrAuth = 0;

                    std::cin >> regOrAuth;

                    Users::User* user = nullptr;
                    switch (regOrAuth)
                    {
                        case 1:
                            printYellow(L"------------ ");
                            printYellow(L"Регистрация");
                            printYellow(L" ------------\n");

                            user = _reg();

                            return user;

                        case 2:
                            printYellow(L"------------ ");
                            printYellow(L"Авторизация");
                            printYellow(L" ------------\n");

                            user = _auth();

                            return user;

                        case 0:
                            printPurple(L"\nДосвидания!\n\n");
                            return nullptr;
                    
                        default:
                            printRed(L"Такой пункт отсутствует\n");
                            break;
                    }
                }
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

                printYellow(L"------------ ");
                printYellow(L"Работа");
                printYellow(L" ------------\n");

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
