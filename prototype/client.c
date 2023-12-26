#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <unistd.h>


int main(){
    struct sockaddr_in server_adrs;
    int network_socket = createAndInitSocket(&server_adrs);

    
    /*

    //create socket
    network_socket = socket(AF_INET,SOCK_STREAM,0);

    //Specify adrs for socket
    struct sockaddr_in server_adrs;
    server_adrs.sin_family  = AF_INET;
    server_adrs.sin_port = htons(9002);
    server_adrs.sin_addr.s_addr = INADDR_ANY;
    */
    //connect 
    /*
    int connect_status = connect(network_socket,(struct sockaddr*) 
    &server_adrs, sizeof(server_adrs));
    */
    if(connectToServer(&server_adrs,network_socket)){
        printf("connection failed\n");
    }

    //receive data from server
    char buffer[255];
    recv(network_socket,&buffer,sizeof(buffer),0);

    //print data that has received
    printf("data receieved: %s",buffer);

    //close socket
    close(network_socket);

	return 0;
}

int createAndInitSocket(struct sockaddr_in * server_adrs){
    int network_socket = (AF_INET,SOCK_STREAM,0);

    server_adrs->sin_family  = AF_INET;
    server_adrs->sin_port = htons(9002);
    server_adrs->sin_addr.s_addr = INADDR_ANY;

    return network_socket;
}

int connectToServer(struct sockaddr* server_adrs,int network_socket){
    return connect(network_socket,(struct sockaddr*) &server_adrs, sizeof(server_adrs));
}


