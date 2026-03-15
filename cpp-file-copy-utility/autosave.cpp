#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include "autosave.h"
using std::cout, std::cin, std::endl;

namespace autosave_tools {

        namespace fs = std::filesystem;

        std::string findFile(const std::string &filename){
            std::string docs = std::getenv("HOME") + std::string("/Documents"); // Assuming the file is in the Documents directory
            for (const auto &entry : fs::recursive_directory_iterator(docs)){
                if (entry.path().filename() == filename){ 
                    return entry.path().string(); // Return the full path of the found file
                }
            }
            return ""; // Return an empty string if the file is not found
        }
    void autosave(){ 

        std::string line;
        std::string SourceName;
        std::string DestName;
        cout<<"Enter File to copy from:  " << endl; 
        std::getline(cin, SourceName);

        std::string fullPath = findFile(SourceName);
        if (fullPath.empty()){
            std::cerr <<"File not found in Documents directory.\n"<<endl; 
            return;
        }
        std::ifstream source(fullPath);

        if (!source){
            std::cerr <<"Could not find the file to read from\n"<<endl; 
            return;
        }
        std::cout<<"Enter the new name of the file to create and copy to : " <<endl;
        std::getline (cin,DestName);

        std::ofstream dest(DestName);

        if(!dest){
            std::cerr<<"Could not create the file." <<endl;
            return;
        }


        while(std::getline(source, line)){
            dest << line<< '\n';
        }
        cout<<"File copied sucessfully.\n"<<endl;  


   }
}

int main() {
    autosave_tools::autosave();  // Call your function
    return 0;
}
 