// #################################### Read Files ####################################
// Notes:   Need to launch the .exe to read a file.
//          
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Controller.hpp"

namespace ext {

    // Forward declaration
    class CsvRead;
    class CsvLine;
    class CsvWrite;


    // Manage a File to read
    class CsvRead {

    public:

        // Constructor
        CsvRead() {}

        // Destructor
        ~CsvRead() {}


        /** 
         * @brief : CSV format reader, 
         *  can pass the file with argument OR
         *  can pass the file path when asked OR
         *  can pass the file path in code.
         * 
         * @param file_path => file path of the csv to read (default "")
         * @param argc      => argument count 
         * @param argv      => argument value
         * @return 
         */
        std::vector<CsvLine> csvReader(std::string file_path = "", int argc = NULL, char* argv[] = nullptr);

    private:

        /** 
         * @brief : Ask the full path of the file for the user.
         * 
         * @return std::vector<CsvLine>
         * 
         */
        std::vector<CsvLine> readFileFromUserEntry();


        /** 
         * @brief : Read and parse a file.
         * 
         * @param file_path     => file path of the csv to read (default "")
         * 
         * @return std::vector<CsvLine>
         */
        std::vector<CsvLine> readFile(std::string file_path = "");
    };


    // Manage the lines of a File
    class CsvLine {

    public:

        // Costructor
        CsvLine() {}

        // Copy constructor
        CsvLine(const CsvLine& other) {
            m_values = other.m_values;
        }

        // Operator overload "="
        CsvLine operator=(const CsvLine& other) {
            m_values = other.m_values;
        }

        // Destructor
        ~CsvLine() {}


        /** 
         * @brief : Parse a line.
         * 
         * @param line (std::string)    => line to parse
         * @param delimiter (char)      => delimiter 
         */
        void parse(std::string line, char delimiter = ',');


        /** 
         * @brief : Return the value at the given column.
         * 
         * @param column (int)  => which position is the value to return
         * 
         * @return (std::string)
         */
        std::string getString(int column);


        /** 
         * @brief : Return the value at the given column.
         * 
         * @param column (int)  => which position is the value to return
         * 
         * @return (double)
         */
        double getDouble(int column);


        /**
         * @brief : Return the value at the given column.
         *
         * @param column (int)  => which position is the value to return
         *
         * @return (int)
         */
        int getInt(int column);

    private:

        std::vector<std::string> m_values;
    };

    // Manage the parsed line 
    class CsvWrite {

    public:

        // Constructor
        CsvWrite() {}

        // Destructor
        ~CsvWrite(){}

        /** 
         * @brief : Insert in a Database the given Vector.
         * 
         * @param lines (std::vector<CsvLine>)  => vector holding lines
         */
        void createHeathInsurance(std::vector<CsvLine> lines);

        // For debug only
        void showParsing(std::vector<CsvLine> lines);
    };

} // namespace ext
