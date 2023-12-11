#ifndef SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H
#define SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H

#endif //SERVER_CLIEN_COMMUNICATION_IN_C_USERMANAGEMENTUTIL_H

#define BUFFER_SIZE 255
#define MAX_USERS 255
#include "hashTable.h"

int writeTableToTXT(USER_TABLE * TABLE){
    char * file = "serverDomain/userList.txt";
    FILE *fp = fopen(file, "w");
    if(fp==NULL) return -1;
    int i;
    for(i=0;i<TABLE->tableSize;i++){
        fprintf(fp,"%s,%s",TABLE->table->userName,TABLE->table->userName);
    }
    fclose(fp);
    return 0;
}

USER_TABLE * readTableFromTXT(USER_TABLE * TABLE){
    printf("1");
    int i=0;
    char * tokens[2];
    char buffer[BUFFER_SIZE];
    USER_TABLE_NODE tempNode;
    printf("11");
    FILE *fp = fopen("userList.txt", "r");
    printf("22");
    if(fp==NULL) return NULL;
    printf("1");
    while (fgets(buffer,MAX_USERS ,fp))
        i++;
    TABLE = createTable(TABLE,0.3,i);
    printf("2");
    while (fgets(buffer,MAX_USERS ,fp)){
        //read string from file
        tokens[0] = strtok(buffer,",");
        tokens[1] = strtok(buffer,",");
        addElementToTable(TABLE,tokens[0],tokens[1]);
    }
    return TABLE;
}

int createUserDocuments(){
    return 0;
}

int createNewUser(USER_TABLE* TABLE){
    char buffer[BUFFER_SIZE];
    printf("Please enter user name:\n");
    scanf("%s",buffer);
    char* userName = (char*)calloc(strlen(buffer),sizeof(char));
    strcpy(userName,buffer);
    if(findUser(TABLE,userName)==0){
        printf("this user already exists!\n");
        free(userName);
        userName=NULL;
        return -1;
    }
    printf("Please enter your password:\n");
    scanf("%s",buffer);
    char* userPassword = (char*)calloc(strlen(buffer),sizeof(char));

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

int removeUser(){
    return 0;
}