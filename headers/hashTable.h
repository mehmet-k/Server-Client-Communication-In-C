#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>

#define BUFFER_SIZE 255

typedef struct user_table_node{
    char* userName;
    char* password;
    char* telephoneNumber;
    char* name;
    char* surname;
    int isDeleted;
}USER_TABLE_NODE;

typedef struct user_table_node_buffer{
    char userName[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    char telephoneNumber[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char surname[BUFFER_SIZE];
}USER_TABLE_NODE_BUFFER;

typedef struct user_table{
    USER_TABLE_NODE * table;
    int tableSize;
}USER_TABLE;

//print table 
//inputs : table, table size
int viewTable(USER_TABLE *TABLE){
    if(TABLE==NULL) return -1;
    USER_TABLE_NODE * table = TABLE->table;
    int M = TABLE->tableSize;
    int i;
    for(i=0;i<M;i++){
        if(table[i].isDeleted==0 && table[i].userName!=NULL)
            printf("%d. %s\n",i,table[i].userName);
        else
            printf("%d. ------\n",i);
    }
    return 0;
}

//finds a prime number that is suitable for table size
//inputs number of elemnts (N), load factor
//return: prime number(table size)
int findSuitablePrimeNumber(float N,float loadfactor){
    int num = N/loadfactor;
    int i=2;
    num--;
    while (i<sqrt(num)){ //might not be the most efficient way to this...
        num++;
        i=2;
        while(num%i!=0 && i<sqrt(num)) i++;
    }
    return num;
}

//create table, initalize it's values
//inputs: pointer of table,table size
//return: table
USER_TABLE_NODE* initializeTable(USER_TABLE_NODE*table, int M){
    table = (USER_TABLE_NODE*) malloc((M)*sizeof (USER_TABLE_NODE));
    if(table==NULL) return NULL;
    int i;
    for(i=0;i<M;i++){
        table[i].password = NULL;
        table[i].userName = NULL;
        table[i].isDeleted = 0;
    }
    return table;
}

//create table
//inputs : table,load factor, number of elements, table size
//table size will be calculated within findSuitablePrimeNumber;
//return: tablo, M(table size)
USER_TABLE * createTable(USER_TABLE *TABLE, float loadfactor, int N){
    TABLE = (USER_TABLE*) calloc(1,sizeof (USER_TABLE));
    TABLE->tableSize = findSuitablePrimeNumber((float)N,loadfactor);
    TABLE->table =  initializeTable(TABLE->table,TABLE->tableSize);
    return TABLE;
}

//1. hash function
int hashFunction(unsigned long long value, int M){
    return value%M;
}

//2. hash function
int hashFunction2(unsigned long long value, int M){
    return 1+(value%(M-2));
}

//double hashing
int DoubleHash(unsigned long long value,int M,int i,int mod,char* userName){
    int h1= hashFunction(value,M);
    int h2= hashFunction2(value,M);
    int dh = (h1 + i*h2)%M;
    if(mod==2){
        printf("h1(\"%s\")%d\n",userName,h1);
        printf("h2(\"%s\")%d\n",userName,h2);
        printf("dh(\"%s\")%d\n",userName,dh);
    }
    return dh;
}

//by using Horner's method, transform given string
//into a integer value, so it can be hashed
//returns calculated value corresponding to userName 
unsigned long long numerizeUserName(char userName[]){
    int size = strlen(userName);
    int i=0,prime=17;
    unsigned long long total = 1*(userName[i]);//birler basama��n�n de�eri
    for(i=1;i<size;i++){
        total += ((userName[i])*prime); 
        prime*= prime;//prime karesi al
    }
    return total;
}

//call traverseTable function depending on mod
//mod = 1 normal 
//mod = 2 debug 
int traverseTable(USER_TABLE *TABLE, char userName[]){
    unsigned long long numerizedUserName = numerizeUserName(userName);
    USER_TABLE_NODE * table = TABLE->table;
    int i;
    int j=1;
    i = DoubleHash(numerizedUserName,TABLE->tableSize,j,1,userName);
    //if the element not deleted before or if it is not   //if userName's doesn't match
    //equal to NULL, continue 							  //continue searching
    while ( (table[i].isDeleted==1 || table[i].userName!=NULL) && strcmp(table[i].userName,userName) != 0 && i!=TABLE->tableSize){
        j++;//increase j value to recall hash function                                      //if table size not reached
        i = DoubleHash(numerizedUserName,TABLE->tableSize,j,1,userName);                                   //continue searching
    }
    return i;
}


//at the index i of the table, initialize userName
//and assign values userName and isDeleted
//returns index
int initializeElement(USER_TABLE_NODE* table, USER_TABLE_NODE_BUFFER userInformations, int i){
    table[i].userName = (char*)calloc(strlen(userInformations.userName),sizeof (char));
    strcpy(table[i].userName,userInformations.userName);

    table[i].password = (char*)calloc(strlen(userInformations.password),sizeof (char));
    strcpy(table[i].userName,userInformations.password);

    table[i].password = (char*)calloc(strlen(userInformations.telephoneNumber),sizeof (char));
    strcpy(table[i].userName,userInformations.telephoneNumber);

    table[i].password = (char*)calloc(strlen(userInformations.name),sizeof (char));
    strcpy(table[i].userName,userInformations.name);

    table[i].password = (char*)calloc(strlen(userInformations.surname),sizeof (char));
    strcpy(table[i].userName,userInformations.surname);

    table[i].isDeleted = 0;

    return i;
}

//check if user exists, if not add it to the table
//if return is not negative, adding user to table was successfull
int addElementToTable(USER_TABLE *TABLE, USER_TABLE_NODE_BUFFER userInformations){
    USER_TABLE_NODE * table = TABLE->table;
    int i = traverseTable(TABLE,userInformations.userName);
    if(table[i].userName == NULL){ //if userName at location i is NULL, place the user here
        return initializeElement(table,userInformations,i);
    }
    else if(strcmp(table[i].userName,userInformations.userName)==0){
        if(table[i].isDeleted==1){ //if user has been deleted before,
            table[i].isDeleted=0;  //assign it as undeleted.
            return i;
        }
        else{
            return -1;
        }
    }
    else if(i==TABLE->tableSize){//table full
        return -2;
    }
    else{
        return -3;
    }
}

void reAddElementToTable(USER_TABLE_NODE * user){
    user->isDeleted = 0;
}

//remove given item from table by assigning isDeleted to 1
USER_TABLE_NODE * removeElementFromTable(USER_TABLE *TABLE,char* userName){
    if(TABLE==NULL) return NULL;
    USER_TABLE_NODE * table=TABLE->table;
    int i = traverseTable(TABLE,userName);
    if(table[i].userName!=NULL && strcmp(userName,table[i].userName)==0 && table[i].isDeleted == 0){
        table[i].isDeleted = 1;
        return &table[i];
    }
    else{
        return NULL;
    }
}

//search for given user
//NULL couldn't find user or table does not exist
//USER_TABLE_NODE address = found User adress
USER_TABLE_NODE * findUser(USER_TABLE *TABLE, char * userName){
    if (TABLE==NULL) return NULL;
    USER_TABLE_NODE  * table = TABLE->table;
    int i = traverseTable(TABLE,userName);
    if(table[i].userName!=NULL && strcmp(userName,table[i].userName)==0 && table[i].isDeleted == 0){
        return &table[i];
    }
    else{
        return NULL;
    }
}

/*
//recreate the table by getting rid off deleted elements
USER_TABLE_NODE* reHash(USER_TABLE_NODE *table, int M,int mod){
    int count=0,i,newLocation;;
    for(i=0;i<M;i++){
        if(table[i].userName != NULL && table[i].isDeleted == 0){
            count++;//undeleted # elements
        }
    }
    //temporary array that elements will be stored
    USER_TABLE_NODE * tempArr = (USER_TABLE_NODE *) calloc(count,sizeof (USER_TABLE_NODE));
    int j=0;
    for(i=0;i<M;i++){
    	//if user not has been deleted, add it to tempArr
    	//deallocate it's userName are in the table
        if(table[i].userName != NULL && table[i].isDeleted == 0){
            if(mod==2) printf("%d konumundaki %s kullanicisi silinmemis\n",i,table[i].userName);
            tempArr[j].userName = (char*) calloc(12,sizeof (char));
            strcpy(tempArr[j].userName,table[i].userName);
            tempArr[j].isDeleted = 0;
            j++;
            free(table[i].userName);
            table[i].userName=NULL;
        }
        //if user has been deleted, doesn't add it
        //deallocate it's userName are in the table
        else if(table[i].userName != NULL && table[i].isDeleted == 1){
            if(mod==2) printf("%d konumundaki %s kullanicisi silinmis\n",i,table[i].userName);
            free(table[i].userName);
            table[i].userName=NULL;
        }
    }
    //deallocate previous table
    free(table);
    table=NULL;
    //create new table
    USER_TABLE_NODE* newTable = NULL;
    newTable = initializeTable(newTable,M);
    if(newTable==NULL) return NULL;
    for(i=0;i<count;i++){ //hash and place elements in tempArray
        newLocation = addElementToTable(newTable,tempArr[i].userName,M,1);
        if(mod==2) printf("%s isimli kullanicinin tablodaki yeni yeri :%d\n",tempArr[i].userName,newLocation);
    }
    free(tempArr);//deallocate tempArray
    tempArr=NULL;
    return newTable;
}

*/
