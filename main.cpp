#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>

namespace fs = std::filesystem;

int main() {
    std::string folderName = "example_folder";

    if (fs::create_directory(folderName)) {
        std::cout << "Directory created: " << folderName << std::endl;
    } else {
        std::cout << "Directory already exists or could not be created." << std::endl;
    }


}

