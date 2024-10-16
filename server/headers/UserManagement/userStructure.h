#include "userFileManagement.h"

//-1 user doesn't exist
//-2 wrong password
//0 creadientials correct
int checkCredientials(USER_TABLE*TABLE,char*userName,char*password){
    USER_TABLE_NODE  * temp = findUser(TABLE,userName);
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
int addNewUser(USER_TABLE* TABLE,USER_TABLE_NODE_BUFFER userInfo){
    if(addElementToTable(TABLE,userInfo,0)<0){
        return -2;
    }
    //couldn't write to the file properly
    if(TABLE->elementCount == 0){
        if(writeUserTableToTXT(TABLE)<0){
            removeElementFromTable(TABLE,userInfo.userName);
            return -3;
        }
    }
    else{
        if(appendUserInformationToTableTXT(TABLE, findUser(TABLE,userInfo.userName))<0){
            removeElementFromTable(TABLE,userInfo.userName);
            return -3;
        }
    }
    char path[BUFFER_SIZE] = "serverDomain/";
    strcpy(path,userInfo.userName);
    mkdir(path,0777);

    return 0;
}

//-1 user doesn't exist or table doenst exist
//-2 couldn't write to file
//0 success
int removeUser(USER_TABLE * TABLE,char * userName){
    USER_TABLE_NODE * temp = removeElementFromTable(TABLE,userName);
    if(temp==NULL) return -1;
    else if(writeUserTableToTXT(TABLE)<0){
        reAddElementToTable(temp);
        return -2;
    }
    else return 0;
}

