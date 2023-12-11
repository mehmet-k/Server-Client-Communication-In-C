#ifndef SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H
#define SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H

#endif //SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H

#include "userFileManagement.h"

//-1 user doesn't exist
//-2 wrong password
//0 creadientials correct
int checkCredientials(USER_TABLE*TABLE,char*userName,char*password){
    USER_TABLE_NODE * temp = findUser(TABLE,userName);
    if(temp==NULL) return -1;
    else{
        if(strcmp(temp->password,password)!=0) return -2;
        else return 0;
    }
}

//-1 username already exists
//-2 couldn't add to user table
//-3 couldn't write to the file
//0 success
int createNewUser(USER_TABLE* TABLE,char * bufferName, char * bufferPassword){
    char* userName = (char*)calloc(strlen(bufferName),sizeof(char));
    strcpy(userName,bufferName);
    if(findUser(TABLE,userName)!=NULL){
        free(userName);
        userName=NULL;
        return -1;
    }
    char* userPassword = (char*)calloc(strlen(bufferPassword),sizeof(char));
    //couldn't add user properly
    if(addElementToTable(TABLE,userName,userPassword)<0){
        return -2;
    }
    //couldn't write to the file properly
    if(writeTableToTXT(TABLE)<0){
        removeElementFromTable(TABLE,userName);
        return -3;
    }
    return 0;
}

//-1 user doesn't exist or table doenst exist
//-2 couldn't write to file
//0 success
int removeUser(USER_TABLE * TABLE,char * userName){
    USER_TABLE_NODE * temp = removeElementFromTable(TABLE,userName);
    if(temp==NULL) return -1;
    else if(writeTableToTXT(TABLE)<0){
        addElementToTable(TABLE,temp->userName,temp->password);
        return -2;
    }
    else return 0;
}

