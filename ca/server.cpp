#include "server.h"

void failure(string error){
    cout<<error<<endl;
	_exit(1);
}

void build_server(int socketfd, struct sockaddr_in *server_address, int port_number){
	bzero((char *) server_address, sizeof(server_address));
	server_address->sin_family = AF_INET;
	server_address->sin_port = htons(port_number);
	server_address->sin_addr.s_addr = INADDR_ANY;

	if (bind(socketfd, (struct sockaddr *) server_address, sizeof(*server_address)) ==-1){ 
		failure("binding has problem!\n");
    }
	if(listen(socketfd,5)==-1)
		failure("problem in listening!");
}
