#include "stdio.h"
#include "headers/Menu/MenuTextResource.h"
#include "headers/Menu/MenuConfig.h"

int main(){
    
    int isExit = MenuConfig_getMainMenuExitValue();
    int menuSelection;

    do{
        displayMainMenu();
        scanf("%d", &menuSelection);
        switch (menuSelection)
        {
        case 1:
            /* display chats */
            break;
        case 2:
            /* add contact */
            break;
        case 3:
            /* remove contact */
            break;
        case 4:
            /* start new chat */
            break;
        case 5:
            /* leads to exit */
            break;
        default:
            displayUnknownOperationMessage();
            break;
        }
    }while (menuSelection != isExit);   

    return 0;
}

