cmake_minimum_required(VERSION 3.22)
project(FileManagementSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(FileManagementSystem main.cpp DoublyLinkList.h Stack.h FileStructure.cpp FileStructure.h)
