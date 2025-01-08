#pragma once

#include "PlukiPluki.h"

#include "struct/Aliases/AliasRules.h"
#include "struct/Aliases/custom/String/Rules/StringAliasRules.h"
#include "struct/Aliases/custom/String/Full/StringAliasFull.h"

#include <string>
#include <vector>
#include <map>
#include <exception>
#include <iostream>
#include <regex>

namespace DBs
{
    typedef std::map<std::string, Aliases::AliasRules*> __aliases;
    typedef std::map<std::string, std::string>          __responseData;
    typedef std::vector<std::string>                    __stringVec;
    typedef unsigned short                              __amountCols;

    class DB 
    {
        private:
            enum ERROR_STATUS
            {
                SUCCESS,
                INDEX_OUT_OF_RANGE,
                DATA_INVALID,
                ALIASES_HAVE_DUPLICATES,
            };

            std::string _getErrorMsgByStatus (
                                                ERROR_STATUS error
                                             ) const noexcept;

            bool        _areAnyDuplicates    (
                                                const __aliases& aliases
                                             ) const noexcept;

            // std::vector<Aliases::AliasRules*> _mapToVec(const std::map<std::string, Aliases::AliasRules*>& map) const;

            // Strings Tool:
            __stringVec _split               (
                                                const std::string& str, 
                                                const std::string& sep
                                             ) const;

        protected:
            mutable PlukiPlukiLib::PlukiPluki* _connect;

            std::string                        _DB_IN_ROW_SEPARATOR;

            __aliases                          _aliases;

            void _destruct                             () 
                                                        noexcept;

            // Is correct
            bool _isCorrect                            (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        std::string                 DB_IN_ROW_SEPARATOR,
                                                        const __aliases&            aliases
                                                       ) const;

            bool _isCorrectImpl                        (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        std::string                 DB_IN_ROW_SEPARATOR,
                                                        const __aliases&            aliases
                                                       ) const noexcept;

            bool            _isCorrectRow              (
                                                        const std::string& row, 
                                                        const std::string& DB_IN_ROW_SEPARATOR,
                                                        const __aliases&  aliases
                                                       ) const;             

            bool            _isCorrectRowImpl          (
                                                        const std::string& row, 
                                                        const std::string& DB_IN_ROW_SEPARATOR,
                                                        const __aliases&   aliases
                                                       ) const noexcept; 

            bool            _isCorrectRowByAliases     (
                                                        const __stringVec& splitRow, 
                                                        const __aliases&   aliases
                                                       ) const;

            bool            _isCorrectRowByAliasesImpl (
                                                        const __stringVec& splitRow, 
                                                        const __aliases&   aliases
                                                       ) const noexcept;

            // Get row
            __responseData _getRow                     (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                       ) const;

            __stringVec    _getRowImpl                 (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                       ) const noexcept;

            // Set row
            void            _setRow                    (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                       );

            ERROR_STATUS    _checkIsRowSetted          (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                       ) noexcept;

            void            _setRowImpl                (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                        ) noexcept;                

            // void _setByIndex(
            //     PlukiPlukiLib::PlukiPluki*& connect, 
            //     const std::map<std::string, Aliases::AliasRules*>& aliases,
            //     PlukiPlukiLib::__amountRows rowIndex, 
            //     std::vector<std::string> newData,
            //     std::string DB_BEGIN_VALUE,
            //     std::string DB_END_VALUE,
            //     std::string DB_IN_ROW_SEPARATOR
            // );

            // void _add(
            //     PlukiPlukiLib::PlukiPluki*& connect, 
            //     const std::map<std::string, Aliases::AliasRules*>& aliases,
            //     std::vector<std::string> data,
            //     std::string DB_BEGIN_VALUE,
            //     std::string DB_END_VALUE,
            //     std::string DB_IN_ROW_SEPARATOR
            // );

        public:
            DB                    (
                                    std::string      path, 
                                    std::string      DB_IN_ROW_SEPARATOR,
                                    const __aliases& aliases
                                  );

            ~DB                   ();

            // std::string getDbBeginValue()    const;

            // std::string getDbEndValue()      const;

            // std::string getDbRowsSeparator() const;

            bool isCorrect        ()
                                    const;

            __responseData getRow (PlukiPlukiLib::__amountRows index) 
                                    const;

            void           setRow (
                                    PlukiPlukiLib::__amountRows index, 
                                    const __stringVec&          newRow
                                  );

            // void                               add(std::vector<std::string> data);

            // Call getRow
            __responseData operator[] (PlukiPlukiLib::__amountRows index) 
                                        const;

            // Call setRow
            void           operator() (
                                        PlukiPlukiLib::__amountRows index, 
                                        const __stringVec&          newRow
                                      );
    };
};
