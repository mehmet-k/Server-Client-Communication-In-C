#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "headers/IOutil.h"

int main() {

    USER_TABLE * TABLE = NULL;
    TABLE = readUserTableFromTXT(TABLE);

    /*
        init server
    */

    /*
        listen and manage server here
    */

   
    //int status;
    //if(status = close(socketID)) printf("unable to close the server!!\n");
    return 0;
}


