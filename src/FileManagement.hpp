// #################################### Read Files ####################################
// Notes:   Need to launch the .exe to read a file.
//          
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Typedef.hpp"


namespace ext {

    // Forward declaration
    class CsvRead;
    class CsvLine;
    class CsvWrite;

    // Manage a File to read
    class CsvRead {

    public:

        // Constructor
        CsvRead(void) {}

        // Destructor
        ~CsvRead(void) {}


        /** 
         * @brief : CSV format reader, 
         *  can pass the file with argument OR
         *  can pass the file path when asked OR
         *  can pass the file path in code.
         * 
         * @param file_path => file path of the csv to read (default = "")
         * @param argc      => argument count (default = NULL)
         * @param argv      => argument value (default = nullptr)
         * @return 
         */
        std::vector<CsvLine> csvReader(
            const std::string& file_path = "",
            int argc = NULL,
            char* argv[] = nullptr
        );

    private:

        /** 
         * @brief : Ask the full path of the file for the user.
         * 
         * @return std::vector<CsvLine>
         * 
         */
        std::vector<CsvLine> readFileFromUserEntry(void);


        /** 
         * @brief : Read and parse a file.
         * 
         * @param file_path     => file path of the csv to read (default = "")
         * 
         * @return std::vector<CsvLine>
         */
        std::vector<CsvLine> readFile(const std::string& file_path = "");
    };



    // Manage the lines of a File
    class CsvLine {

    public:

        // Constructor
        CsvLine(void) {}

        // Copy constructor
        CsvLine(const CsvLine& other) {
            m_values = other.m_values;
        }

        // Operator overload "="
        CsvLine operator=(const CsvLine& other) {
            m_values = other.m_values;
        }

        // Destructor
        ~CsvLine(void) {}


        /** 
         * @brief : Parse a line.
         * 
         * @param line (std::string)    => line to parse
         * @param delimiter (char)      => delimiter (default = ,)
         */
        void parse(const std::string& line, char delimiter = ',');


        /** 
         * @brief : Return the value at the given column.
         * 
         * @param column (int)  => which position is the value to return
         * 
         * @return (std::string)
         */
        std::string getString(uint16_t column);


        /** 
         * @brief : Return the value at the given column.
         * 
         * @param column (uint16_t)  => which position is the value to return
         * 
         * @return (double)
         */
        double getDouble(uint16_t column);


        /**
         * @brief : Return the value at the given column.
         *
         * @param column (uint16_t)  => which position is the value to return
         *
         * @return (uint16_t)
         */
        uint16_t getInt(uint16_t column);

    private:

        std::vector<std::string> m_values;
    };



    // Manage the parsed line 
    class CsvWrite {

    public:

        // Constructor
        CsvWrite(void) {}

        // Destructor
        ~CsvWrite(void){}

        // For debug only
        void showParsing(const std::vector<CsvLine>& lines);
    };

} // namespace ext
