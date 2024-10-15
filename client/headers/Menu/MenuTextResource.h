#include <stdio.h>

void displayMainMenu(){
    printf("Please choose the operation: \n");
    printf("    1. Display Chats\n");
    printf("    2. Add Contact\n");
    printf("    3. Remove Contact\n");
    printf("    4. Start New Chat\n");
    printf("    5. Exit\n");
}

void displayContacts(){

}

/*
    GENERAL
 */

void displayProceedMessage(){
    printf("Please press enter to proceed.\n");
}

void displayUnknownOperationMessage(){
    printf("Unkown operation. Please try again.\n");
}

/*
    ADD CONTACT
*/

void displayAddContactMessage(){
    printf("To add a new contact please enter following informations:\n");
}

void displayEnterContactNameMessage(){
    printf("Please enter name of the contact: ");
}

void displayEnterContactNumberMessage(){
    printf("Please enter number of the contact: ");
}

void displayContactAddedMessage(){
    printf("Contact is successfully added to your contact list!\n");
}


/* 
    REMOVE CONTACT
*/

void displayRemoveMessage(){
    printf("Please enter number of the contact you wish to remove: ");
}

void displayContactRemovedMessage(){
    printf("Contact is successfully removed from your contact list!\n");
}

/* 
    CHAT
*/

void displayChats(){

}

void displayChatExitMessage(){
    printf("Are you sure you want to exit chat?\n");
    printf("    1. Yes\n");
    printf("    2. No\n");
}