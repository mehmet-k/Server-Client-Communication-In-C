#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

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

void sendMessageToUser(char * message,struct sockaddr* server_adress,int server_socket){
	 //bind the socket to IP and Port
    bind(server_socket,(struct sockaddr*) &server_adress,sizeof(server_adress));
    listen(server_socket,5);
    int client_socket = accept(server_socket,NULL,NULL);
    //send data
    send(client_socket,sv_msg,sizeof(sv_msg),0);
}

