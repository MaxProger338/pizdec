#include "DB.h"

using namespace DBs;
using namespace PlukiPlukiLib;

DB::
    DB( std::string      path, 
        std::string      DB_IN_ROW_SEPARATOR,
        const __aliases& aliases
    ):
        _connect             { new PlukiPluki(path, std::ios::in) },
        _DB_IN_ROW_SEPARATOR { DB_IN_ROW_SEPARATOR                },
        _aliases             { aliases                            }
    {
        // TODO: Решить этот костыль лютый
        short errorKind = 0;
        try
        {
            if (!isCorrect())
            {
                errorKind = 1;
            }
        }
        catch(...)
        {
            _destruct();

            throw std::runtime_error("Error");
        }

        if (errorKind == 1)
        {
            _destruct();

            throw std::runtime_error("DB is invalid!");
        }
    }

DB::
    ~DB()
    {
        _destruct();
    }

void DB::
    _destruct() noexcept
    {
        delete _connect;
        _connect = nullptr;
    }

std::string DB::
    _getErrorMsgByStatus(ERROR_STATUS error) const noexcept
    {
        switch (error)
        {
            // case SUCCESS - должно проверяться перед вызовом функции!
            case INDEX_OUT_OF_RANGE:      return "Index out of range!";
            case DATA_INVALID:         return "Data is invalid!";
            case ALIASES_HAVE_DUPLICATES: return "Alias have duplicates!";

            default:                      return "Unknow file error!";
        }
    }

bool DB::
    _areAnyDuplicates (
        const __aliases& aliases
    ) const noexcept
    {
        __stringVec names(aliases.size());

        for (auto i : aliases)
        {
            if (std::find(begin(names), end(names), i.first) != end(names))
            {
                return true;
            }

            names.push_back(i.first);            
        }

        return false;
    }

// Is correct
bool DB::_isCorrect (
        PlukiPlukiLib::PlukiPluki*& connect, 
        std::string                 DB_IN_ROW_SEPARATOR,
        const __aliases&            aliases
    ) const
    {
        connect->reopen(std::ios::in);

        if (_areAnyDuplicates(aliases))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ALIASES_HAVE_DUPLICATES));
        }

        return _isCorrectImpl(connect, DB_IN_ROW_SEPARATOR, aliases);
    }

bool DB::
    _isCorrectImpl (
        PlukiPlukiLib::PlukiPluki*& connect, 
        std::string                 DB_IN_ROW_SEPARATOR,
        const __aliases&            aliases
    ) const noexcept
    {
        __stringVec rows{ connect->indexAll() };

        __amountRows amountRows = rows.size();
                
        for (size_t i = 0; i < amountRows; i++)
        {
            if (!_isCorrectRowImpl(rows[i], DB_IN_ROW_SEPARATOR, aliases)) 
            {
                return false;
            }
        }
        
        return true;
    }

bool DB::
    _isCorrectRow (
        const std::string& row, 
        const std::string& DB_IN_ROW_SEPARATOR,
        const __aliases&   aliases
    ) const
    {
        if (_areAnyDuplicates(aliases))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ALIASES_HAVE_DUPLICATES));
        }

        return _isCorrectRowImpl(row, DB_IN_ROW_SEPARATOR, aliases);
    }

bool DB::
    _isCorrectRowImpl (
        const std::string& row, 
        const std::string& DB_IN_ROW_SEPARATOR,
        const __aliases&   aliases
    ) const noexcept
    {
        /*
         * В принципе не нужно создавать дубликат строки,
         * но это нужно для будущей модернезации (если такова будет)
         * Тип это имитирует, что перед этим происходят какие-то 
         * токенизации тоже
        */
        std::string newRow = row;

        // токенизируем по DB_IN_ROW_SEPARATOR ('~')
        __stringVec splitRow {
            _split(newRow, DB_IN_ROW_SEPARATOR)
        };

        return _isCorrectRowByAliasesImpl(splitRow, aliases);
    }

bool DB::
    _isCorrectRowByAliases (
        const __stringVec& splitRow, 
        const __aliases&   aliases
    ) const
    {
        if (_areAnyDuplicates(aliases))
        {
            throw std::runtime_error(_getErrorMsgByStatus(ALIASES_HAVE_DUPLICATES));
        }

        return _isCorrectRowByAliasesImpl(splitRow, aliases);
    }

bool DB::
    _isCorrectRowByAliasesImpl (
        const __stringVec& splitRow, 
        const __aliases&   aliases
    ) const noexcept
    {
        if (splitRow.size() != aliases.size())
        {
            return false;
        }

        int index = 0;
        for (auto i : aliases)
        {
            std::string val = splitRow[index++];

            if (!i.second->isValid(val))
            {
                return false;
            }
        }

        return true;
    }

// End Is correct

// Get row
__responseData DB::
    _getRow (
        PlukiPlukiLib::PlukiPluki*& connect, 
        PlukiPlukiLib::__amountRows rowIndex, 
        const __aliases&            aliases,
        const std::string&          DB_IN_ROW_SEPARATOR
    ) const
    {
        connect->reopen(std::ios::in);

        __amountRows amountRows = connect->getAmountRows();

        if (rowIndex >= amountRows)
        {
            throw std::runtime_error(_getErrorMsgByStatus(INDEX_OUT_OF_RANGE));
        }

        __stringVec data = _getRowImpl(connect, rowIndex, aliases, DB_IN_ROW_SEPARATOR);

        __amountCols amountCols = data.size();
        if (amountCols != aliases.size())
        {
            throw std::runtime_error(_getErrorMsgByStatus(DATA_INVALID));
        }

        __responseData response;

        __amountCols index = 0;
        for (auto i : aliases)
        {
            const std::string& dataTmp = data[index++];

            if (!i.second->isValid(dataTmp))
            {
                throw std::runtime_error(_getErrorMsgByStatus(DATA_INVALID));
            }

            response[i.first] = dataTmp; 
        }

        return response;
    }

__stringVec DB::
    _getRowImpl (
        PlukiPlukiLib::PlukiPluki*& connect, 
        PlukiPlukiLib::__amountRows rowIndex, 
        const __aliases&            aliases,
        const std::string&          DB_IN_ROW_SEPARATOR
    ) const noexcept
    {
        std::string row = connect->getRow(rowIndex);

        __stringVec splitRow{ _split(row, DB_IN_ROW_SEPARATOR) };

        return splitRow;
    }

// End Get row

// Set row
void DB::
    _setRow (
        PlukiPlukiLib::PlukiPluki*& connect, 
        PlukiPlukiLib::__amountRows rowIndex, 
        const __stringVec&          newRow,
        const __aliases&            aliases,
        const std::string&          DB_IN_ROW_SEPARATOR
    ) {
        ERROR_STATUS setErrorStatus = _checkIsRowSetted(connect, rowIndex, newRow, aliases, DB_IN_ROW_SEPARATOR);

        if (setErrorStatus != SUCCESS)
        {
            throw std::runtime_error(_getErrorMsgByStatus(setErrorStatus));
        }
    }

DB::ERROR_STATUS DB::
    _checkIsRowSetted (
        PlukiPlukiLib::PlukiPluki*& connect, 
        PlukiPlukiLib::__amountRows rowIndex, 
        const __stringVec&          newRow,
        const __aliases&            aliases,
        const std::string&          DB_IN_ROW_SEPARATOR
    ) noexcept
    {
        connect->reopen(std::ios::in);

        __amountRows amountRows = connect->getAmountRows();

        if (rowIndex >= amountRows)
        {
            return INDEX_OUT_OF_RANGE;
        }

        connect->reopen(std::ios::app);

        __amountCols index = 0;
        for (auto i : aliases)
        {
            const std::string& dataTmp = newRow[index++];

            if (!i.second->isValid(dataTmp))
            {
                return DATA_INVALID;
            }
        }

        _setRowImpl(connect, rowIndex, newRow, DB_IN_ROW_SEPARATOR);

        return SUCCESS;
    }

void DB::
    _setRowImpl (
        PlukiPlukiLib::PlukiPluki*& connect, 
        PlukiPlukiLib::__amountRows rowIndex, 
        const __stringVec&          newRow,
        const std::string&          DB_IN_ROW_SEPARATOR
    ) noexcept
    {
        std::string finalRow;

        int index = 0;
        for (auto i : newRow)
        {
            finalRow += i;

            if (index++ < newRow.size() - 1)
            {
                finalRow += DB_IN_ROW_SEPARATOR;
            }
        }

        connect->setRow(rowIndex, finalRow);
    }

// void DB::
//     _setByIndex(
//         PlukiPlukiLib::PlukiPluki*& connect, 
//         const std::map<std::string, Aliases::AliasRules*>& aliases,
//         PlukiPlukiLib::__amountRows rowIndex, 
//         std::vector<std::string> newData,
//         std::string DB_BEGIN_VALUE,
//         std::string DB_END_VALUE,
//         std::string DB_IN_ROW_SEPARATOR
//     ) {
//         const std::_Ios_Openmode currentMode = connect->getMode();

//         connect->reopen(std::ios::in);

//         __amountRows finalIndex = rowIndex + 1;

//         if (finalIndex >= connect->getAmountRows() - 1)
//         {
//             throw std::runtime_error("Incorrect index!");
//         }

//         connect->reopen(std::ios::app);

//         std::vector<Aliases::AliasRules*> rules{ _mapToVec(aliases) };

//         connect->reopen(std::ios::in);

//         if (!_isCorrectDBView(connect, DB_BEGIN_VALUE, DB_END_VALUE, DB_IN_ROW_SEPARATOR, rules))
//         {
//             throw std::runtime_error("DB is invalid!");
//         }

//         connect->reopen(std::ios::app);

//         if (!_isCorrectRowByAliases(newData, rules))
//         {
//             throw std::runtime_error("Data is invalid (by aliases)");
//         }

//         std::string finalData;

//         int index = 0;
//         for (auto i : newData)
//         {
//             finalData += i;

//             if (index++ < newData.size() - 1)
//             {
//                 finalData += DB_IN_ROW_SEPARATOR;
//             }
//         }

//         connect->setRowByIndex(finalIndex, finalData);

//         connect->reopen(currentMode);
//     }

// void DB::
//     _add(
//         PlukiPlukiLib::PlukiPluki*& connect, 
//         const std::map<std::string, Aliases::AliasRules*>& aliases,
//         std::vector<std::string> data,
//         std::string DB_BEGIN_VALUE,
//         std::string DB_END_VALUE,
//         std::string DB_IN_ROW_SEPARATOR
//     ) {
//         const std::_Ios_Openmode currentMode = connect->getMode();

//         std::vector<Aliases::AliasRules*> rules{ _mapToVec(aliases) };

//         connect->reopen(std::ios::in);

//         int finalIndex = connect->getAmountRows() - 1;

//         if (!_isCorrectDBView(connect, DB_BEGIN_VALUE, DB_END_VALUE, DB_IN_ROW_SEPARATOR, rules))
//         {
//             throw std::runtime_error("DB is invalid!");
//         }

//         connect->reopen(std::ios::app);

//         if (!_isCorrectRowByAliases(data, rules))
//         {
//             throw std::runtime_error("Data is invalid (by aliases)");
//         }

//         std::string finalData;

//         int index = 0;
//         for (auto i : data)
//         {
//             finalData += i;

//             if (index++ < data.size() - 1)
//             {
//                 finalData += DB_IN_ROW_SEPARATOR;
//             }
//         }

//         connect->insertToFile(finalIndex, finalData);

//         connect->reopen(currentMode);
//     }

// std::vector<Aliases::AliasRules*> DB::
//     _mapToVec(const std::map<std::string, Aliases::AliasRules*>& map) const
//     {
//         std::vector<Aliases::AliasRules*> aliases;

//         for (auto i : map)
//         {
//             aliases.push_back(i.second);
//         }

//         return aliases;
//     }

// String Tools
__stringVec DB::
    _split(const std::string& str, const std::string& sep) const
    {
        __stringVec splitStr;

        // TODO: заменить этот алгоритм на какой-нибудь другой
        if (str.find(sep) != std::string::npos)
        {
            std::regex del(sep);

            // Create a regex_token_iterator to split the string
            std::sregex_token_iterator it(str.begin(), str.end(), del, -1);

            // End iterator for the regex_token_iterator
            std::sregex_token_iterator end;

            // Iterating through each token
            while (it != end) 
            {
                if (*it != "")
                {
                    splitStr.push_back(*it);
                }
                ++it;
            }
        }

        return splitStr;
    }

// End String Tools

bool DB::
    isCorrect() const
    {
        return _isCorrect(_connect, _DB_IN_ROW_SEPARATOR, _aliases);
    }

// std::string DB::
//     getDbBeginValue() const
//     {
//         return _DB_BEGIN_VALUE;
//     }

// std::string DB::
//     getDbEndValue() const
//     {
//         return _DB_END_VALUE;
//     }

// std::string DB::
//     getDbRowsSeparator() const
//     {
//         return _DB_IN_ROW_SEPARATOR;
//     }

__responseData DB::
    getRow(__amountRows index) const
    {
        return _getRow(_connect, index, _aliases, _DB_IN_ROW_SEPARATOR);
    }

void DB::
    setRow (
        PlukiPlukiLib::__amountRows index, 
        const __stringVec&          newRow
    ) {
        _setRow(_connect, index, newRow, _aliases, _DB_IN_ROW_SEPARATOR);
    }

// void DB::
//     add(std::vector<std::string> data)
//     {
//         _add(_connect, _cols, data, _DB_BEGIN_VALUE, _DB_END_VALUE, _DB_IN_ROW_SEPARATOR);
//     }

__responseData DB::
    operator[](PlukiPlukiLib::__amountRows index) const
    {
        return getRow(index);
    }
    
void DB::
    operator() (
        PlukiPlukiLib::__amountRows index, 
        const __stringVec&          newRow
    ) {
        setRow(index, newRow);
    }