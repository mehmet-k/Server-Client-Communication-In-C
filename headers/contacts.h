#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct contact_node{
    char * userName;
    char * telephoneNumber;
    struct contact_node *next;
}CONTACT_NODE;

CONTACT_NODE * initNode(char * username,char * telephonenumber){
    CONTACT_NODE * contactNode = (CONTACT_NODE*) malloc(sizeof(CONTACT_NODE));
    contactNode->telephoneNumber = (char *) malloc(strlen(telephonenumber)*sizeof(char ));
    strcpy(contactNode->telephoneNumber,telephonenumber);
    contactNode->userName = (char *) malloc(strlen(username)*sizeof(char ));
    strcpy(contactNode->userName,username);
    return contactNode;
}

CONTACT_NODE * addContactNodeToEnd(CONTACT_NODE *head,CONTACT_NODE * node){
    CONTACT_NODE * tmp = head;
    if(head==NULL){
        node->next = head;
        head=node;
    }
    else{
        while(tmp->next!=NULL && strcmp(tmp->userName,node->userName)!=0) tmp = tmp->next;
        if(strcmp(tmp->userName,node->userName)!=0){
            tmp->next = node;
            node->next = NULL;
        }
    }
    return head;
}

void printContacts(CONTACT_NODE * head){
    CONTACT_NODE * tmp = head;
    if(head!=NULL){
        while(tmp!=NULL) {
            printf("username : %s\n",tmp->userName);
            tmp = tmp->next;
        }
    }
}

void removeContact(CONTACT_NODE * head,char * username){
    CONTACT_NODE * tmp = head,*tmp2;
    while(tmp->next->next!=NULL && strcmp(tmp->next->userName,username)!=0) tmp = tmp->next;
    if(strcmp(tmp->next->userName,username)==0){
        tmp2 = tmp->next;
        tmp->next = tmp->next->next;
        free(tmp2);
    }
}