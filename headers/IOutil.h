#include "userManagementUtil.h"

int getUser(USER_TABLE * TABLE){
    USER_TABLE_NODE_BUFFER temp;
    printf("please enter following information:\n");
    printf("your user name: ");
    USER_TABLE_NODE * check=NULL;
    do{
        scanf("%s",temp.userName);
        if(strcmp("exit",temp.userName)==0) return -1;
        check = findUser(TABLE,temp.userName);
        if(check!=NULL){
            printf("this user name already exists!\nplease enter a user name again or type 'exit' to abort: ");
        }
    } while (check!=NULL && strcmp("exit",temp.userName)!=0);
    check=NULL;

    printf("please enter password: ");
    scanf("%s",temp.password);

    printf("your telephone number: ");
    do{
        scanf("%s",temp.telephoneNumber);
        if(strcmp("exit",temp.telephoneNumber)==0) return -1;
        //check = findUser(TABLE,temp.userName); //to be implemented later
        check = NULL;
        if(check!=NULL){
            printf("another user with this phone number already exists!\n"
                   "please enter a phone number again or type 'exit' to abort: ");
        }
    } while (check!=NULL );

    printf("please enter your name: ");
    scanf("%s",temp.name);

    printf("please enter your surname: ");
    scanf("%s",temp.surname);

    return addNewUser(TABLE,temp);
}