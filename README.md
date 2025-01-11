```bash
clang++ -fsanitize=address src/main.cpp src/components/DB/WrapperDB/WrapperDB.cpp src/data/SymbolsArrays.cpp src/components/DB/UsersDataDB/UsersDataDB.cpp src/components/DB/AdminsDataDB/AdminsDataDB.cpp src/components/DB/AccountsDB/AccountsDB.cpp src/modules/DB/DB.cpp libs/PlukiPluki-Lib/bin/PlukiPluki.a -I libs/PlukiPluki-Lib/include -o build/app.out; ./build/app.out; rm build/app.out
```