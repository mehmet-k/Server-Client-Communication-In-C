#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h>

// IPv4 AF_INET sockets:
typedef struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
}SOCKADDR_IN;

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

/* Description of data base entry for a single host.  */
struct hostent
{
  char *h_name;			/* Official name of host.  */
  char **h_aliases;		/* Alias list.  */
  int h_addrtype;		/* Host address type.  */
  int h_length;			/* Length of address.  */
  char **h_addr_list;		/* List of addresses from name server.  */
};

int createSocket(SOCKADDR_IN * server){
    int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		printf("Could not create socket");
        return -1;
	}
		
	server->sin_addr.s_addr = inet_addr("74.125.235.20");
	server->sin_family = AF_INET;
	server->sin_port = htons( 80 );
    return socket_desc;
}

int connectServer(SOCKADDR_IN * server,int socket_desc){
    if (connect(socket_desc , (SOCKADDR_IN*)(&server) , sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}

	puts("Connected");
    return 0;
}

int bindSocket(int socket_desc,SOCKADDR_IN server){
    //Bind
    if( bind(socket_desc,(SOCKADDR_IN *)(&server) , sizeof(server)) < 0){
        puts("bind failed");
    }
    puts("bind done");
}

int sendData(int socket_desc){
    char * message = "GET / HTTP/1.1\r\n\r\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	
	return 0;
}

int receiveData(int socket_desc,char* server_reply){
    //Receive a reply from the server
	if( recv(socket_desc, server_reply ,strlen(server_reply) , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply);
	
	return 0;
}

int acceptConnection(int socket_desc,struct sockaddr client){
    int new_socket,c;
    //Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)(&client), (socklen_t*)&c);
	if (new_socket<0)
	{
		perror("accept failed");
	}
	
	puts("Connection accepted");

	return new_socket;
}