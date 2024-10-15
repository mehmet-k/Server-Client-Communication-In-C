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
    
    if(mkdir(directory,0777)) return -2;

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

        addElementToTable(TABLE,userInfo,0);
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


int setUserDirectory(char * userName){
    char path[BUFFER_SIZE] = "serverDomain/";
    strcat(path,userName);
    mkdir(path,0777);
    strcat(path,"/chats");
    mkdir(path,0777);
    strcpy(path,"serverDomain/");
    return 0;
}

int appendContactToTXT(USER_TABLE_NODE  * user,CONTACT_NODE * node){
    char path[BUFFER_SIZE] = "serverDomain/";
    strcat(path,user->userName);
    strcat(path,"/contacts.txt");
    FILE *fp = fopen(path, "a");

    if(fp==NULL)  {
        printf("couldn't open contacts file\n");
        return -1;
    }

    fprintf(fp,"%s,%s\n",node->userName,node->telephoneNumber);

    fclose(fp);
    return 0;
}


int createTXTandSaveContact(USER_TABLE_NODE  * user,CONTACT_NODE * node){
    char path[BUFFER_SIZE] = "serverDomain/";
    strcat(path,user->userName);
    strcat(path,"/contacts.txt");
    FILE *fp = fopen(path, "w");
    if(fp==NULL) {
        printf("%s\n",path);
        return -1;
    }

    fprintf(fp,"%s,%s\n",node->userName,node->telephoneNumber);

    fclose(fp);
    return 0;
}

int saveContact(USER_TABLE_NODE  * user,CONTACT_NODE  * head,CONTACT_NODE * node){
    if(head==node) return createTXTandSaveContact(user,head);
    else return appendContactToTXT(user,node);
}

int getContacts(USER_TABLE_NODE * user){
    char path[BUFFER_SIZE] = "serverDomain/";
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE],telephonenumber[BUFFER_SIZE];
    char * token;
    strcat(path,user->userName);
    strcat(path,"/contacts.txt");
    FILE * fp= fopen(path,"r");
    if(fp == NULL) return -1;
    CONTACT_NODE * node;
    while (fgets(buffer,MAX_USERS ,fp)){
        //read string from file
        token = strtok(buffer,",");
        strcpy(username,token);

        token = strtok(NULL,",");
        strcpy(telephonenumber,token);
        node = initNode(username,telephonenumber);
        user->contact_head  = addContactNodeToEnd(user->contact_head,node);
    }
    return 0;
}

int readContacts(USER_TABLE  * TABLE,char * username){
    return getContacts(findUser(TABLE,username));
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
    char path[BUFFER_SIZE] = "serverDomain/";
    TABLE = createTable(TABLE,0.2,i);
    USER_TABLE_NODE  * temp;
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

        addElementToTable(TABLE,userInfo,0);

        //setUserDirectory(userInfo.userName);

        readContacts(TABLE,userInfo.userName);

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

    fclose(fp);
    return 0;
}

int writeUserContactsToFile(USER_TABLE * contacts,char * directory){
    FILE *fp = fopen("directory", "w");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    int i;
    for(i=0;i<contacts->elementCount;i++){
        if(contacts->table[i].userName != NULL && contacts->table[i].isDeleted==0)
            fprintf(fp,"%s,%s\n",contacts->table[i].userName,contacts->table[i].telephoneNumber);
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
    writeUserContactsToFile(user->contacts,directory);
    return 0;
}

int readUserContactsFromFile(USER_TABLE_NODE *user,char * directory){
    char buffer[BUFFER_SIZE],* token;
    createContactTable(user);
    FILE * fp = fopen("directory", "r");
    if(fp==NULL) {
        fclose(fp);
        return -1;
    }
    USER_TABLE_NODE_BUFFER user_buffer;
    while (fgets(buffer,MAX_USERS ,fp)){
        token = strtok(buffer,",");
        strcpy(user_buffer.userName,token);

        token = strtok(NULL,",");
        strcpy(user_buffer.telephoneNumber,token);

        //addElementToContactTable(contacts,NULL);
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
    readUserContactsFromFile(user,directory);
    return 0;
}
