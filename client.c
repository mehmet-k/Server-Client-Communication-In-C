#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT_SERVER 2000

int main(){

    int clientID = socket(AF_INET,SOCK_STREAM,0);
    if(clientID) return -1;
    
    char * ip = "235.3.42.1";
    struct  sockaddr_in address;
    address.sin_port = htons(PORT_SERVER);
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr.s_addr);
   
   int status = connect(clientID,&address,sizeof(address));

   if(status){
        printf("connection was unsuccessfull!\n");
        return -1;
   }
   else{
        printf("connection succesfull\n");
   }

    
    return 0;
}

