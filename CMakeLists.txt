cmake_minimum_required(VERSION 3.26)
project(Project3b)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3b main.cpp
        MaxHeap.h
        CharacterStats.cpp
        CharacterStats.h
        CustomMap.h
        Iterator.h)
