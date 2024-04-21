//
// Created by Dhananjaya on 2023-10-20.
//

#include "FileStructure.h"
#include <fstream>


FileStructure::FileStructure(std::string currentPath) : currentPath{currentPath} {
    changeCurrentFolder(currentPath);
}

enum FileFolderStatus FileStructure::createFolder(std::string directoryName) {
    std::string fullPath = currentPath + "/" + directoryName;
    if (!fs::exists(fullPath)) {
        if (fs::create_directory(fullPath)) {
            fs::directory_entry entry(fullPath);
            filesFoldersList->append(entry);
            return successful;
        } else {
            return failToCreate;
        }
    } else {
        return alreadyExist;
    }
}


enum FileFolderStatus FileStructure::createFile(std::string name) {
    std::string fullPath = currentPath + "/" + name;
    if (!fs::exists(fullPath)) {
        std::ofstream file(fullPath);
        if (file.is_open()) {
            file.close();
            filesFoldersList->append(fs::directory_entry(fullPath));
            return successful;
        } else {
            return failToCreate;
        }
    } else {
        return alreadyExist;
    }
}


enum DeleteState FileStructure::deleteFileOrFolder(std::string name) {
    std::string fullPath = currentPath + "/" + name;
    if (fs::exists(fullPath)) {
        if (fs::remove(fullPath)) {
            auto fileNode = filesFoldersList->begin();
            int n = 0;
            while (fileNode) {

                if (fileNode->value.path() == fullPath) {
                    filesFoldersList->remove(n);
                    return deletionSuccessful;
                }
                n++;
                fileNode = fileNode->next;
            }

        }
        return failedToDelete;

    }
    return fileDoesntExist;
}

enum DeleteState FileStructure::deleteFileOrFolder(int index) {
    if (index < filesFoldersList->length) {
        auto fullPath = filesFoldersList->get(index)->value.path();
        if (fs::exists(fullPath)) {
            if (fs::remove(fullPath)) {
                filesFoldersList->remove(index);
                return deletionSuccessful;
            }
            return failedToDelete;

        }
        return fileDoesntExist;
    }
    return fileDoesntExist;
}

//int FileStructure::sizeToInt(fs::directory_entry directory){
//    return directory.file_size();
//}
//
//void FileStructure::sortFilesAndFolders(enum SortBasedOn basedOn) {
//
//    if (size ==  basedOn){
//        quickSort(filesFoldersList->begin(), filesFoldersList->end(), const_cast<std::function<int(fs::directory_entry)>&>(sizeToInt));
//    }
//}
//
//void FileStructure::swap(dll::Node<fs::directory_entry> *firstNode, dll::Node<fs::directory_entry> *secondNode) {
//    auto temp = firstNode->value;
//    firstNode->value = secondNode->value;
//    secondNode->value = temp;
//}
//
//
//
//void FileStructure::pivot(dll::Node<fs::directory_entry> *startNode, dll::Node<fs::directory_entry> *endNode, std::function<int(fs::directory_entry)> &compareFunction) {
//    auto pivotNode = startNode;
//    auto j = startNode;
//    if (startNode->value == endNode->value || startNode->value == endNode->next->value) {
//        return;
//    }
//    for (auto i = startNode->next; i < endNode->next; i = i->next) {
//        if (compareFunction(i->value) < compareFunction(pivotNode->value) && i != j) {
//            j++;
//            swap(i, j);
//
//        }
//    }
//    swap(j, pivotNode);
//    pivot(startNode, j->previous, compareFunction);
//    pivot(j->next, endNode, compareFunction);
//}
//
//void FileStructure::quickSort(dll::Node<fs::directory_entry> *startNode, dll::Node<fs::directory_entry> *endNode,const std::function<int(fs::directory_entry)> &compareFunction) {
//    pivot(startNode, endNode, const_cast<std::function<int(fs::directory_entry)> &>(compareFunction));
//}

bool FileStructure::getAllFiles(std::string path = "") {
    try {
        for (auto &entry: fs::directory_iterator(path)) {
            filesFoldersList->append(entry);
        }
    } catch (fs::filesystem_error &e) {
        return false;
    }
    return true;
}


bool FileStructure::writeToFiles(std::string nameOfFile, std::string text) {
    std::string fullPath = currentPath + "/" + nameOfFile;
    std::ofstream file(fullPath);
    if (file.is_open()) {
        file << text;
        file.close();
        return true;
    }
    return false;
}

bool FileStructure::writeToFiles(int index, std::string text) {
    std::string fullPath = filesFoldersList->get(index)->value.path();
    std::ofstream file(fullPath);
    if (file.is_open()) {
        file << text;
        file.close();
        return true;
    }
    return false;
}


bool FileStructure::changeCurrentFolder(std::string path) {
    if (path[0] == '/') {
        currentPath = path;
    } else {
        currentPath = currentPath + "/" + path;
    }
    if (fs::exists(currentPath)) {
        history.push(filesFoldersList);
        filesFoldersList = new dll::DoublyLinkList<fs::directory_entry>();
        getAllFiles(currentPath);

        return true;
    }
    return false;
}

bool FileStructure::changeCurrentFolder(int index) {
    return changeCurrentFolder(filesFoldersList->get(index)->value.path());
}

bool FileStructure::goBack() {
    if (!history.isEmpty()) {
        delete filesFoldersList;
        filesFoldersList = history.peek();
        history.pop();
        currentPath = getCurrentWorkingDirectory();
        return true;
    }
    return false;
}

fs::path FileStructure::getCurrentWorkingDirectory() {
    fs::path fullPath(filesFoldersList->get(0)->value.path());
    fs::path workingDirectory = fullPath.parent_path();
    return workingDirectory;
}


FileStructure::~FileStructure() {
    while (!history.isEmpty()) {
        dll::DoublyLinkList<fs::directory_entry> *removingList = history.peek();
        delete removingList;
        history.pop();
    }
}


void FileStructure::listAllFilesAndFolders(bool indexMode) {
    auto temp = filesFoldersList->begin();
    int index = 0;
    std::cout
            << "===========================================================================================================================================================\n";

    while (temp != nullptr) {
        if (temp->value.is_directory()) {
            if (indexMode) {
                std::cout << index << " | ";
            }
            std::cout << "\033[32m" << temp->value.path().filename() << std::endl;
        } else {
            if (indexMode) {
                std::cout << index << " | ";
            }
            std::cout << "\033[34m" << temp->value.path().filename() << std::endl;
        }
        std::cout << "\033[0m";
        temp = temp->next;
        index++;
    }
}










