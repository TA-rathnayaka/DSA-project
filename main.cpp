#include <iostream>
#include <string>
#include "DoublyLinkList.h"
#include "Stack.h"
#include "FileStructure.h"


void display(bool start) {
    if (start) {
        std::cout
                << "===========================================================================================================================================================\n"
                << "File Management System 🗂️" << std::endl;
    } else {
        std::cout
                << "===========================================================================================================================================================\n"
                << "1 - create files 📁 | 2 - create folders 📂 | 3 - delete file 🗑️ | 4 - delete folders 🗑️ | 5 - go to 🚪 | 6 - go back 👈 | 7 - write to files 📝 | 8 - change mode | 9 - quite \n"
                << "===========================================================================================================================================================\n"
                << std::endl;
    }

}

void changeMode(int &userInput, bool &isIndexMode) {
    while (userInput != 0 && userInput != 1) {
        std::cout << "Select the mode \n0 - Index mode (recommended)\n1 - Names mode" << std::endl;
        std::cin >> userInput;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (userInput == 0) {
            std::cout << "You are now on index mode" << std::endl;
            isIndexMode = true;
        } else if (userInput == 1) {
            isIndexMode = false;
            std::cout << "You are now on Names mode" << std::endl;
        } else {
            std::cout << "Wrong input" << std::endl;
        }
    }
}

void fileOrFolderValidation(bool isFile, FileFolderStatus fileStatus) {
    std::string type;
    if (isFile) {
        type = "file";
    } else {
        type = "folder";
    }
    if (successful == fileStatus) {
        std::cout << type << " created successful" << std::endl;
    } else if (alreadyExist == fileStatus) {
        std::cout << type << " already exist" << std::endl;
    } else {
        std::cout << "Failed to create file" << std::endl;
    }

}

void DeleteValidation(bool isFile, DeleteState fileStatus) {
    std::string type;
    if (isFile) {
        type = "file";
    } else {
        type = "folder";
    }
    if (deletionSuccessful == fileStatus) {
        std::cout << type << " deleted successfully" << std::endl;
    } else if (fileDoesntExist == fileStatus) {
        std::cout << type << " doesn't exist" << std::endl;
    } else {
        std::cout << "Failed to delete file" << std::endl;
    }

}


int main() {
    auto structure = FileStructure("/Users/crysis/Documents/Screenshot/main");

    bool isIndexMode = true;
    int userInput = 0;
    int index;
    std::string fileName;
    std::string folderName;
    std::string text;
    FileFolderStatus fileStatus;
    DeleteState deleteState;

    while (userInput != 9) {
        display(true);
        structure.listAllFilesAndFolders(isIndexMode);
        display(false);
        system("clear");
        std::cin >> userInput;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (userInput) {
            case 1:
                std::cout << "Enter the file name you want to create?" << std::endl;
                std::cin >> fileName;

                fileStatus = structure.createFile(fileName);
                fileOrFolderValidation(true, fileStatus);
                break;
            case 2:
                std::cout << "Enter the folder name you want to create?" << std::endl;
                std::cin >> folderName;
                fileStatus = structure.createFolder(folderName);
                fileOrFolderValidation(false, fileStatus);
                break;
            case 3:
                if (!isIndexMode) {
                    std::cout << "Enter the file name You want to delete?" << std::endl;
                    std::cin >> fileName;
                    deleteState = structure.deleteFileOrFolder(fileName);
                } else {
                    std::cout << "Choose the file you want to remove from index" << std::endl;
                    std::cin >> index;
                    deleteState = structure.deleteFileOrFolder(index);
                }
                DeleteValidation(true, deleteState);
                break;
            case 4:
                if (!isIndexMode) {
                    std::cout << "Enter the folder name You want to delete?" << std::endl;
                    std::cin >> fileName;
                    structure.deleteFileOrFolder(fileName);
                } else {
                    std::cout << "Choose the folder you want to remove from index" << std::endl;
                    std::cin >> index;
                    structure.deleteFileOrFolder(index);
                }
                DeleteValidation(false, deleteState);
                break;
            case 5:

                if (isIndexMode) {
                    std::cout << "Enter the folder index You want to go?" << std::endl;
                    std::cin >> index;
                    if (structure.changeCurrentFolder(index)) {
                        std::cout << "Working directory changed to " << structure.currentPath << std::endl;
                    } else {
                        std::cout << "No such folder called " << folderName << std::endl;
                    }
                } else {
                    std::cout << "Enter the folder name You want to go?" << std::endl;
                    std::cin >> folderName;
                    if (structure.changeCurrentFolder(folderName)) {
                        std::cout << "Working directory changed to " << structure.currentPath << std::endl;
                    } else {
                        std::cout << "No such folder called " << folderName << std::endl;
                    }
                }
                break;
            case 6:
                std::cout << "going back?" << std::endl;
                if (structure.goBack()) {
                    std::cout << "Working directory changed to " << structure.currentPath << std::endl;
                } else {
                    std::cout << "You don't have access to that folder" << std::endl;
                }
                break;
            case 7:
                if (!isIndexMode) {
                    std::cout << "Enter the name of the file you want to write to" << std::endl;
                    std::cin >> fileName;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter text you want to write" << std::endl;
                    std::getline(std::cin, text);
                    if (structure.writeToFiles(fileName, text)) {
                        std::cout << "Successfully written to file" << std::endl;
                    } else {
                        std::cout << "Failed to write to file" << std::endl;
                    }
                }else {
                    std::cout << "Enter the name of the file index you want to write to" << std::endl;
                    std::cin >> index;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter text you want to write" << std::endl;
                    std::getline(std::cin, text);
                    if (structure.writeToFiles(index, text)) {
                        std::cout << "Successfully written to file" << std::endl;
                    } else {
                        std::cout << "Failed to write to file" << std::endl;
                    }
                }
                break;
            case 8:
                changeMode(userInput, isIndexMode);
                break;
        }
    }
    return 0;
}



