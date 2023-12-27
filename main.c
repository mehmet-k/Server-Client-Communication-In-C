#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "headers/IOutil.h"
#include "headers/sockUtil.h"
void * client(USER_TABLE * TABLE);

int main() {

    USER_TABLE * TABLE = NULL;
    TABLE = readUserTableFromTXT(TABLE);
    USER_TABLE_NODE * mehmet = findUser(TABLE,"mehmetK");
    CONTACT_NODE * node = initNode("test","test");
    mehmet->contact_head = addContactNodeToEnd(mehmet->contact_head,node);
    viewTable(TABLE);
    int True=1;
    while(True){
        client(TABLE);
    }
    
    //int status;
    //if(status = close(socketID)) printf("unable to close the server!!\n");
    return 0;
}

int viewLoginMenuAndReturnOption(){
    int option;
    printf("Please choose what would you like to do:\n");
    do{
        printf("----------------------------------\n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("3. Close the app\n");
        printf("----------------------------------\n");
        scanf(" %d",&option);
        if(option>3 || option <1) printf("This operation doesnt exists! Please choose again.\n");
    }while(option>=3 || option <1);
    return option;
}

int viewMenuAndReturnOption(){
    int option;
    printf("Please choose what would you like to do:\n");
    do{
        printf("----------------------------------\n");
        printf("1. Chats\n");
        printf("2. Add a new contact.\n");
        printf("3. Delete a contact.\n");
        printf("4. Log Out\n");
        printf("----------------------------------\n");
        scanf(" %d",&option);
        if(option>4 || option <1) printf("This operation doesnt exists! Please choose again.\n");
    }while(option>4 || option <1);
    return option;
}

USER_TABLE_NODE * login(USER_TABLE * TABLE){
    char username[BUFFER_SIZE],password[BUFFER_SIZE];
    printf("Please enter your username:\n");
    scanf("%s",username);
    printf("Please enter your password:\n");
    scanf("%s", password);
    USER_TABLE_NODE * user = findUser(TABLE,username);
    int status = checkCredientials(TABLE,username,password, user);
    fflush(stdin);
    if(status == 0) return user;
    if(status==-1) printf("this user name doesn't exist!\n");
    else printf("wrong password!\n");
    return NULL;
}

void signUp(USER_TABLE * TABLE){
    getUser(TABLE);
}

void deleteAccount(USER_TABLE * TABLE){
    deleteUser(TABLE);
}

USER_TABLE_NODE  * addContact(USER_TABLE_NODE * user){
    char username[BUFFER_SIZE],telephonenumber[BUFFER_SIZE];
    printf("Remember to enter the informations correctly, otherwise you can't send message to these users!\n");
    printf("Please enter username of your contact: \n");
    scanf("%s",username);
    printf("Please enter password of your contact: \n");
    scanf("%s",telephonenumber);

    CONTACT_NODE * node = initNode(username,telephonenumber);
    user->contact_head = addContactNodeToEnd(user->contact_head, node);
    return user;
}

void deleteContact(USER_TABLE_NODE * user){
    char username[BUFFER_SIZE];
    printf("Please enter username of your contact you wish to delete: \n");
    scanf("%s",username);
    if(removeElementFromTable(user->contacts,username)==0){
        printf("Succesfully removed the contact.");
    }
    else{
        printf("Couldn't find contact in the contact list!\n");
    }

}

void openChat(USER_TABLE_NODE * user){
    char buffer[BUFFER_SIZE];
    do{
        printf("Please enter the username of user you want to send message or:\ntype 'back' to return to previous menu");
        scanf("%s",buffer);
        if(findUser(user->contacts,buffer)==0){
            //send message
        }
        else{
            printf("couldn't find this user in the contact list!\n");
        }
    }while(strcmp(buffer,"back")!=0);
}
void viewContacts(USER_TABLE_NODE * user){
    viewTable(user->contacts);
}

void chats(USER_TABLE * TABLE, USER_TABLE_NODE * user){
    printf("Please enter what you want to do:\n");
    int option,status;
    do{
        printf("----------------------------------\n");
        printf("1. Send message to an user.\n");
        printf("2. View contacts\n");
        printf("3. Back\n");
        printf("----------------------------------\n");
        scanf(" %d",&option);
        if(option == 1) openChat(user);
        else if(option == 2) {
            printContacts(user->contact_head);
            if(user->contact_head == NULL) printf("You have no contacts!\n");
        }
        else if(option>3 || option < 1) printf("Illegal operation, please try again.\n");
    }while(option!=3);
}

void * client(USER_TABLE * TABLE){
    USER_TABLE_NODE * user = NULL;
    int status_login,status_menu;
    do{
        status_login = viewLoginMenuAndReturnOption();
        if(status_login==2){
            signUp(TABLE);
        }
        if(status_login==1){
            user = login(TABLE);
            if(user != NULL){
                printf("----------------------------\n");
                printf("Loggen in as: %s",user->userName);
                printf("----------------------------\n");
                do{
                    status_menu = viewMenuAndReturnOption();
                    if(status_menu == 1){
                        chats(TABLE,user);
                    }
                    else if(status_menu == 2){
                        user = addContact(user);
                    }
                    else if(status_menu == 3){
                        deleteContact(user);
                    }
                }while(status_menu!=4);
            }
        }
    }while(status_login!=3);
}
