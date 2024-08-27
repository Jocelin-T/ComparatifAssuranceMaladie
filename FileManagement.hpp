// #################################### Read Files ####################################
// Notes:   Need to launch the .exe to read a file.
//          
#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace ext {
    class FileManagement {
    public:
        FileManagement() {};

        void readFileInCmdLine(int argc, char* argv[]);

        void getFileFromUser();

    };
} // namespace rf
