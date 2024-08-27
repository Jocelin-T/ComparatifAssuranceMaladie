#include "FileManagement.hpp"


namespace ext {



    void FileManagement::readFileInCmdLine(int argc, char* argv[]) {
        // Program arguments (when launching with console)
        std::cout << "argc: " << argc << "\n";

        if (argc < 2) {
            std::cout << "Missing file name as argument\n";
            return;
        }

        for (int i = 0; i < argc; i++) {
            std::cout << "\t" << argv[i] << "\n";
        }

        // File object
        std::ifstream input_file;
        input_file.open(argv[1]);

        // Check if the file opened successfully
        if (!input_file.is_open()) {
            std::cerr << "Error: Could not open the file " << argv[1] << "\n";
            return;
        }

        // Read data
        std::string line;
        std::cout << "File Content: \n";
        while (getline(input_file, line)) {
            std::cout << line << "\n"; // Print the current line 
        }

        std::system("pause");
        input_file.close();
    }



    void FileManagement::getFileFromUser() {
        std::string filename{ "" };
        std::ifstream input_file{ "" };

        while (!input_file.is_open()) {

            // Prompt the user to enter the file name
            std::cout << "File path should look like that: C:/Users/YourSession/Folder/Your_file.csv\n";
            std::cout << "Enter the full path of the file: ";
            std::cin >> filename;

            input_file.open(filename);

            // Check if the file opened successfully
            if (!input_file.is_open()) {
                std::cerr << "Error: Could not open the file " << filename << "\n";
            }
        }

        std::cout << "File opened successfully.\n";

        // Read and print each line
        std::string line;
        while (std::getline(input_file, line)) {
            std::cout << line << "\n";
        }

        std::system("pause");
        input_file.close();
    }

} // namespace rf
