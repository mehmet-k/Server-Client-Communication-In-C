#include <stdio.h>

#include "headers/userManagementUtil.h"

int main() {
    USER_TABLE * TABLE = NULL;
    TABLE = readTableFromTXT(TABLE);
    viewTable(TABLE);

    char * name1 = "basel\0";
    char * pass1 = "12421\0";
    createNewUser(TABLE,name1,pass1);
    printf("--------------------------\n");
    viewTable(TABLE);
    printf("--------------------------\n");
    removeUser(TABLE,name1);
    viewTable(TABLE);

    return 0;
}


