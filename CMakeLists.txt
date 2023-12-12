cmake_minimum_required(VERSION 3.21)
project(Server_Client_Communication_In_C C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(Server_Client_Communication_In_C
        headers/hashTable.h
        headers/userFileManagement.h
        headers/userManagementUtil.h
        client.c
        main.c)
