cmake_minimum_required(VERSION 3.28)

add_library(SingleLinkedList STATIC SingleLinkedList.cpp)

add_executable(SingleLinkedListApp main.cpp)

target_link_libraries(SingleLinkedListApp PRIVATE SingleLinkedList)