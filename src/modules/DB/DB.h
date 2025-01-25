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
#include <sstream>

namespace DBs
{
    typedef std::map<std::string, std::string> __responseData;
    typedef std::vector<std::string>           __stringVec;
    typedef unsigned short                     __amountCols;
    // TODO: Исправь это недоразумение!!!
    typedef unsigned short                     __amountRowsInDB;

    struct AliasAndHisName
    {
        std::string          name  = "";
        Aliases::AliasRules* alias = nullptr;

        AliasAndHisName(const std::string& name, Aliases::AliasRules* alias):
            name{ name }, alias{ alias } {}
    };

    typedef std::vector<AliasAndHisName>       __aliases;

    class DB 
    {
        private:
            enum ERROR_STATUS
            {
                SUCCESS,
                INDEX_OUT_OF_RANGE,
                DATA_INVALID,
                ALIASES_HAVE_DUPLICATES,
                DB_INVALID,
            };

            std::string _getErrorMsgByStatus (
                                                ERROR_STATUS error
                                             ) const noexcept;

            bool        _areAnyDuplicates    (
                                                const __aliases& aliases
                                             ) const noexcept;

            // Strings Tool:
            __stringVec _split               (
                                                const std::string& str, 
                                                const std::string& sep
                                             ) const;

        protected:
            mutable PlukiPlukiLib::PlukiPluki* _connect;

            std::string                        _DB_IN_ROW_SEPARATOR;

            const __aliases&                   _aliases;

            void           _destruct                  () 
                                                        noexcept;

            // Is correct
            bool           _isCorrect                 (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        std::string                 DB_IN_ROW_SEPARATOR,
                                                        const __aliases&            aliases
                                                      ) const;

            bool           _isCorrectImpl             (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        std::string                 DB_IN_ROW_SEPARATOR,
                                                        const __aliases&            aliases
                                                      ) const noexcept;

            bool           _isCorrectRow              (
                                                        const std::string& row, 
                                                        const std::string& DB_IN_ROW_SEPARATOR,
                                                        const __aliases&  aliases
                                                      ) const;             

            bool           _isCorrectRowImpl          (
                                                        const std::string& row, 
                                                        const std::string& DB_IN_ROW_SEPARATOR,
                                                        const __aliases&   aliases
                                                      ) const noexcept; 

            bool           _isCorrectRowByAliases     (
                                                        const __stringVec& splitRow, 
                                                        const __aliases&   aliases
                                                      ) const;

            bool           _isCorrectRowByAliasesImpl (
                                                        const __stringVec& splitRow, 
                                                        const __aliases&   aliases
                                                      ) const noexcept;

            // Get amount rows                 
            __amountRowsInDB   _getAmountRows         (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) const;

            __amountRowsInDB   _getAmountRowsImpl     (
                                                        PlukiPlukiLib::PlukiPluki*& connect
                                                      ) const noexcept;

            // Get row
            __responseData _getRow                    (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) const;

            __stringVec    _getRowImpl                (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) const noexcept;

            // Set row
            void           _setRow                    (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      );

            ERROR_STATUS   _checkIsRowSetted          (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) noexcept;

            void           _setRowImpl                (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        PlukiPlukiLib::__amountRows rowIndex, 
                                                        const __stringVec&          newRow,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) noexcept;                

            // Add row
            void           _addRow                    (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        const __stringVec&          row,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      );

            ERROR_STATUS   _checkIsRowAdded           (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        const __stringVec&          row,
                                                        const __aliases&            aliases,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) noexcept;

            void           _addRowImpl                (
                                                        PlukiPlukiLib::PlukiPluki*& connect, 
                                                        const __stringVec&          row,
                                                        const std::string&          DB_IN_ROW_SEPARATOR
                                                      ) noexcept;

        public:
            DB                              (
                                                std::string      path, 
                                                std::string      DB_IN_ROW_SEPARATOR,
                                                const __aliases& aliases
                                            );

            ~DB                             ();

            std::string    getRowsSeparator () 
                                                const;

            bool isCorrect                  ()
                                                const;

            // TODO: поправь код-стайл!
            __amountRowsInDB getAmountRows  () 
                                                const;

            __responseData getRow           (PlukiPlukiLib::__amountRows index) 
                                                const;

            void           setRow           (
                                                PlukiPlukiLib::__amountRows index, 
                                                const __stringVec&          newRow
                                            );

            void           addRow           (const __stringVec& data);

            // Call getAmountRows
            __amountRowsInDB operator()     ()
                                                const;

            // Call getRow
            __responseData operator[]       (PlukiPlukiLib::__amountRows index) 
                                                const;

            // Call setRow
            void           operator()       (
                                                PlukiPlukiLib::__amountRows index, 
                                                const __stringVec&          newRow
                                            );
            
            // Call addRow
            void           operator()       (const __stringVec& row);
    };
};
