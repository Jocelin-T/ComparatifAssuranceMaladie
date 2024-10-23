#include "FileManagement.hpp"
#include "Config.hpp"

namespace ext {

    // Reader
    std::vector<CsvLine> CsvRead::csvReader(const std::string& file_path, int argc, char* argv[]) {
        // Program arguments (when launching with console)
        std::cout << "Arguments Count (argc): " << argc << "\n";

        if (argc >= 2) {
            std::cout << "File is read from argument\n";
            return readFile(argv[1]);
        }

        if (file_path.empty()) {
            std::cout << "File is read from user entry\n";
            return readFileFromUserEntry();
        }
        
#if DEBUG
        if (!file_path.empty()) {
            std::cout << "File is read from code line\n";
            return readFile(file_path);
        }
#endif // DEBUG

        else {
            std::cout << "Error: Impossible to open a file \n";
        }
    }


    // Read the file if is given as full path by the user
    std::vector<CsvLine> CsvRead::readFileFromUserEntry(void) {

        std::string file_path{ "" };
        std::ifstream input_file{ "" };

        while (!input_file.is_open()) {

            // Prompt the user to enter the file name
            std::cout << "File path should look like that: C:/Users/YourSession/Folder/Your_file.csv\n";
            std::cout << "Enter the full path of the file: ";
            std::cin >> file_path;
            input_file.open(file_path.c_str());
        }
        input_file.close();
        return readFile(file_path);
    }


    // Read a file
    std::vector<CsvLine> CsvRead::readFile(const std::string& file_path) {

        std::ifstream input_file{ "" };
        input_file.open(file_path.c_str());

        // Check if the file opened successfully
        if (!input_file.is_open()) {
            std::cerr << "Error: Could not open the file " << file_path << "\n";
        }
        
        std::cout << "File opened successfully.\n";

        std::string line{ "" };
        std::vector<CsvLine> lines; // Vector holding line

        // Read each line and push it in a vector
        while (std::getline(input_file, line)) {
            CsvLine csv_line;
            csv_line.parse(line);
            lines.push_back(csv_line);
        }

        input_file.close();
        return lines;
    }


    // Parse each line with a delimiter (default is ",") and add them to m_values
    void CsvLine::parse(const std::string& line, char delimiter) {

        std::stringstream in_line(line);
        std::string temp_column{ "" };

        while (std::getline(in_line, temp_column, delimiter)) {
            m_values.push_back(temp_column);
        }
    }


    // Return a string stock in m_values
    std::string CsvLine::getString(uint16_t column) {
        return m_values[column];
    }


    // Return a double stock in m_values
    double CsvLine::getDouble(uint16_t column) {
        return atof(m_values[column].c_str());
    }


    // Return a uint16_t stock in m_values
    uint16_t CsvLine::getInt(uint16_t column) {
        return atof(m_values[column].c_str());
    }


    // For debug only, display all lines
    void CsvWrite::showParsing(const std::vector<CsvLine>& lines) {

        for (CsvLine line : lines) {

            uint16_t i{ 0 };

            while (i < 6) {
                std::cout << line.getDouble(i) << '\n';
                i++;
            }

            std::cout << line.getString(i) << '\n';
            i++;

            while (i < 13) {
                std::cout << line.getDouble(i) << '\n';
                i++;
            }
            std::cout << "=====================================================\n";
        }
    }

} // namespace ext
