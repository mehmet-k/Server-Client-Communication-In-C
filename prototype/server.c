#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <unistd.h>


int main(){
    char sv_msg[256] = "You have succesfully connected to the server.";

    //create socket
    int server_socket = socket(AF_INET,SOCK_STREAM,0);

    //def the server adrs
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(9002);
    server_adress.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to IP and Port
    bind(server_socket,(struct sockaddr*) &server_adress,
    sizeof(server_adress));

    listen(server_socket,5);

    
    int client_socket = accept(server_socket,NULL,NULL);

    //send data
    send(client_socket,sv_msg,sizeof(sv_msg),0);

    close(server_socket);

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