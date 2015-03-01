/**
* File "main.cpp"
* Created by Sina on Sun Mar  1 17:19:44 2015.
*/

#include "Header.h"
#include "server.h"

int main(){
    int socketfd, socket_accept_fd, port_number,read_status,max_fd;
    char buffer[256];
    bzero(&buffer,256);
    struct sockaddr_in server_address, client_address;
    fd_set server,read_fds;
    FD_ZERO(&server);
    FD_ZERO(&read_fds);
    port_number = atoi(CA_PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) 
        failure("problem in openning socket!");

    build_server(socketfd, &server_address,port_number);
    FD_SET(0,&server);
    FD_SET(socketfd,&server);
    max_fd = socketfd;

    while(1){
        read_fds = server;
        if(select(max_fd+1,&read_fds,NULL,NULL,NULL) < 0)
            failure("problem in sockets select!");
        int i;
        for( i=0; i<=max_fd ; i++){
            if(FD_ISSET(i , &read_fds)){
                if(i==0){
                    // input 
                }
                else if(i!=socketfd){
                    //client or server
                }
                else{
                    //there is a new connection
                    socklen_t client_address_size;
                    client_address_size = sizeof(client_address);
                    socket_accept_fd = accept(socketfd, (struct sockaddr *) &client_address, &client_address_size);
                    if (socket_accept_fd ==-1)
                        failure("problem in accept");
                    FD_SET(socket_accept_fd,&server);
                    if(socket_accept_fd>max_fd)
                        max_fd = socket_accept_fd;
                    cout<<"new client connected.\n";
                }
            }
        }//for
        //check for entery file owner!!!
    }

    return 0;
}
