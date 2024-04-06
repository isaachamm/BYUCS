cmake_minimum_required(VERSION 3.21)
project(lab7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab7
        BST.cpp
        BST.h
        BSTInterface.h
        main.cpp
        Node.cpp
        Node.h
        NodeInterface.h)
