#include "hashTable.h"

int isContactExists(USER_TABLE * TABLE,char * contactname){
    if(findUser(TABLE,contactname)!=NULL) return 0;
    else return -1;
}

void messageMenu(USER_TABLE * TABLE,USER_TABLE_NODE * user){
    char buffer[BUFFER_SIZE];
    int option_deletion,option;

    do{
        printf("Please enter the username of the contact you want to send message:\n");
        scanf("%s",buffer);
        if(searchContacts(user->contact_head,buffer)!=1){
            printf("This contact doesn't exists in your contact list!\n");
        }
        else if(findUser(TABLE,buffer)!=NULL){
            printf("No user with this username exists! Do you wish to remove this contact?");
            printf("1.Yes\n2.No\n");
            scanf("%d",&option_deletion);
            if(option_deletion == 1) removeContact(user->contact_head,buffer);
        }
        else{
            //start chat
        }
        printf("1.Send another message.\n");
        printf("2.Back.\n");
        scanf("%d",&option);
        if(option!=1 && option!=2) printf("Illegal opeartion, please choose again.\n");
    } while (option>=2 || option<1);

}