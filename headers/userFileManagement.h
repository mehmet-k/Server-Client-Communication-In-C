//
// Created by MEHMET on 11.12.2023.
//

#ifndef SERVER_CLIEN_COMMUNICATION_IN_C_USERCREDIENTIALS_H
#define SERVER_CLIEN_COMMUNICATION_IN_C_USERCREDIENTIALS_H

#endif //SERVER_CLIEN_COMMUNICATION_IN_C_USERCREDIENTIALS_H

#define BUFFER_SIZE 255
#define MAX_USERS 255
#include "hashTable.h"

USER_TABLE * readTableFromTXT(USER_TABLE * TABLE){
    int i=0;
    char * token;
    char *tokens[2];
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("serverDomain/userList.txt", "r");
    if(fp==NULL) {
        fclose(fp);
        return NULL;
    }
    while (fgets(buffer,MAX_USERS ,fp))
        i++;
    fclose(fp);
    fp= fopen("serverDomain/userList.txt","r");
    if(fp==NULL) {
        fclose(fp);
        return NULL;
    }
    TABLE = createTable(TABLE,0.2,i);
    while (fgets(buffer,MAX_USERS ,fp)){
        //read string from file
        token = strtok(buffer,",");
        tokens[0] = token;
        token = strtok(buffer,",");
        tokens[1] = token;
        addElementToTable(TABLE,tokens[0],tokens[1]);
    }
    fclose(fp);
    return TABLE;
}
int writeTableToTXT(USER_TABLE * TABLE){
    char * file = "serverDomain/userList.txt";
    FILE *fp = fopen(file, "w");
    if(fp==NULL) return -1;
    int i;
    for(i=0;i<TABLE->tableSize;i++){
        if(TABLE->table[i].userName!=NULL && TABLE->table[i].isDeleted==0)
            fprintf(fp,"%s,%s",TABLE->table->userName,TABLE->table->userName);
    }
    fclose(fp);
    return 0;
}



int createUserDocuments(){
    return 0;
}
