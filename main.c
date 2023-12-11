#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util/userManagementUtil.h"

int main() {
    USER_TABLE * TABLE = NULL;
    TABLE = readTableFromTXT(TABLE);
    viewTable(TABLE);

    return 0;
}


