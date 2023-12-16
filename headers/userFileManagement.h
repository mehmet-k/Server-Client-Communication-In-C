#include "hashTable.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 255
#define MAX_USERS 255

int createUserDirectory(USER_TABLE * TABLE, char *userName){
    USER_TABLE_NODE * user;

    char directory[BUFFER_SIZE] = "serverDomain/users/";
    user = findUser(TABLE,userName);
    if(user==NULL) return -1;

    strcat(directory,userName);
    if(mkdir(directory)) return -2;

    return 0;
}

int readUserInformationFromTXT(USER_TABLE * TABLE,char * username){
    char * token;
    char buffer[BUFFER_SIZE];
    char directory[BUFFER_SIZE] = "serverDomain/users/";
    strcat(directory,username);
    strcat(directory,".txt");
    USER_TABLE_NODE_BUFFER userInfo;
    FILE *fp;
    fp= fopen(directory,"r");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    while (fgets(buffer,MAX_USERS ,fp)){
        //read string from file
        token = strtok(buffer,",");
        strcpy(userInfo.userName,token);

        token = strtok(NULL,",");
        strcpy(userInfo.password,token);

        token = strtok(NULL,",");
        strcpy(userInfo.telephoneNumber,token);

        token = strtok(NULL,",");
        strcpy(userInfo.name,token);

        token = strtok(NULL,",");
        strcpy(userInfo.surname,token);

        addElementToTable(TABLE,userInfo);
    }
    fclose(fp);
    return 0;
}

int writeUserInformationToTxt(USER_TABLE * TABLE, char * userName){
    char directory[BUFFER_SIZE] = "serverDomain/userList.txt";
    strcat(directory,userName);
    strcat(directory,".txt");
    FILE *fp = fopen(directory, "w");
    if(fp==NULL) return -1;
    USER_TABLE_NODE * user = findUser(TABLE,userName);
    fprintf(fp,"%s,%s,%s,%s,%s",user->userName,user->password,
            user->telephoneNumber,user->name,user->surname);
    fclose(fp);
    return 0;
}

USER_TABLE * readUserTableFromTXT(USER_TABLE * TABLE){
    int i=0;
    char * token;
    char buffer[BUFFER_SIZE];
    USER_TABLE_NODE_BUFFER userInfo;
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
        strcpy(userInfo.userName,token);

        token = strtok(NULL,",");
        strcpy(userInfo.password,token);

        token = strtok(NULL,",");
        strcpy(userInfo.telephoneNumber,token);

        token = strtok(NULL,",");
        strcpy(userInfo.name,token);

        token = strtok(NULL,",");
        strcpy(userInfo.surname,token);
        printf("%s",userInfo.surname);

        addElementToTable(TABLE,userInfo);
    }
    fclose(fp);
    return TABLE;
}

int writeUserTableToTXT(USER_TABLE * TABLE){
    FILE *fp = fopen("serverDomain/userList.txt", "w");
    if(fp==NULL) return -1;
    int i=0;
    int count=0;
    USER_TABLE_NODE * table = TABLE->table;
    while (count<TABLE->elementCount){
        if(table[i].userName!=NULL && table[i].isDeleted==0){
            count++;
            fprintf(fp,"%s,%s,%s,%s,%s",table[i].userName,table[i].password,
                    table[i].telephoneNumber,table[i].name,table[i].surname);
            printf("count %d elementCount:%d\n",count,TABLE->elementCount);
            //if(count<TABLE->elementCount) fprintf(fp,"\n");
        }
        i++;
    }
    fclose(fp);
    return 0;
}

int appendUserInformationToTableTXT(USER_TABLE * TABLE, USER_TABLE_NODE * user){
    FILE *fp = fopen("serverDomain/userList.txt", "a");
    if(fp==NULL) return -1;
    fprintf(fp,"\n%s,%s,%s,%s,%s",user->userName,user->password,
            user->telephoneNumber,user->name,user->surname);

    return 0;
}

int writeUserContactsToFile(CONTACT_NODE_ARRAY * contacts,char * directory){
    FILE *fp = fopen("directory", "w");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    int i;
    for(i=0;i<contacts->arraySize;i++){
        fprintf(fp,"%s,%s\n",contacts->array[i].userName,contacts->array[i].phoneNumber);
    }
    fclose(fp);
    return 0;
}

int saveUserContacts(USER_TABLE * TABLE, char * userName){
    char * token;
    char buffer[BUFFER_SIZE];
    char directory[BUFFER_SIZE] = "serverDomain/users/";
    strcat(directory,userName);
    strcat(directory,"contacts.txt");
    USER_TABLE_NODE * user = findUser(TABLE,userName);
    writeUserContactsToFile(&user->contacts,directory);
    return 0;
}

int readUserContactsFromFile(CONTACT_NODE_ARRAY * contacts,char * directory){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("directory", "r");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    int i=0;
    while (fgets(buffer,MAX_USERS ,fp)){
        i++;
    }
    contacts->array = (CONTACT_NODE*) calloc(i,sizeof (CONTACT_NODE));
    fclose(fp);
    fp = fopen("directory", "r");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    i=0;
    while (fgets(buffer,MAX_USERS ,fp)){
        contacts->array->userName = (char *) calloc(strlen(buffer),sizeof (char ));
        strcpy(contacts->array[i].userName, buffer);
    }
    fclose(fp);
    return 0;
}

int getUserContacts(USER_TABLE *TABLE,char * userName){
    char * token;
    char buffer[BUFFER_SIZE];
    char directory[BUFFER_SIZE] = "serverDomain/users/";
    strcat(directory,userName);
    strcat(directory,"contacts.txt");
    USER_TABLE_NODE * user = findUser(TABLE,userName);
    readUserContactsFromFile(&user->contacts,directory);
    return 0;
}
