//
// Created by Dhananjaya on 2023-10-20.
//
#include <filesystem>
#include <sstream>
#include "DoublyLinkList.h"
#include "Stack.h"


#ifndef FILEMANAGEMENTSYSTEM_FILESTRUCTURE_H
#define FILEMANAGEMENTSYSTEM_FILESTRUCTURE_H
namespace fs = std::__fs::filesystem;

enum SortBasedOn {
    name, createdDate, size
};

enum FileFolderStatus {
    successful, alreadyExist, failToCreate
};

enum DeleteState {
    deletionSuccessful, fileDoesntExist, failedToDelete
};


class FileStructure {

private:
    dll::DoublyLinkList<fs::directory_entry> *filesFoldersList = new dll::DoublyLinkList<fs::directory_entry>();
    stack::Stack<dll::DoublyLinkList<fs::directory_entry> *> history;

//    void pivot(dll::Node<fs::directory_entry>* startNode, dll::Node<fs::directory_entry> *endNode, std::function<int(fs::directory_entry)> &compareFunction);
//
//    void swap(dll::Node<fs::directory_entry>* firstNode, dll::Node<fs::directory_entry> *secondNode);
//
//    void quickSort(dll::Node<fs::directory_entry> *startNode, dll::Node<fs::directory_entry> *endNode,const std::function<int(fs::directory_entry)> &compareFunction);
//
//    int sizeToInt(fs::directory_entry directory);


public:

    std::string currentPath;

    FileStructure(std::string currentPath);

    bool getAllFiles(std::string path);

    FileFolderStatus createFile(std::string name);

    FileFolderStatus createFolder(std::string directoryName);

    bool writeToFiles(std::string nameOfFile, std::string text);

    bool writeToFiles(int index, std::string text);

    enum DeleteState deleteFileOrFolder(std::string name);

    enum DeleteState deleteFileOrFolder(int index);

//    void sortFilesAndFolders(enum SortBasedOn basedOn);

    bool changeCurrentFolder(std::string path);

    bool changeCurrentFolder(int index);

    fs::path getCurrentWorkingDirectory();

    bool goBack();

    void listAllFilesAndFolders(bool indexMode = false);

    ~FileStructure();


};


#endif //FILEMANAGEMENTSYSTEM_FILESTRUCTURE_H
