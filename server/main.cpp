#include "Header.h"

int main(){
    int socketfd, socket_accept_fd, port_number,read_status,max_fd;
    char buffer[MAX_MSG_SIZE];
    bzero(&buffer,MAX_MSG_SIZE);
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


    mkdir("./Candidates")


    while(1){
        read_fds = server;
        if(select(max_fd+1,&read_fds,NULL,NULL,NULL) < 0)
            failure("problem in sockets select!");
        int clinet_fd;
        for( clinet_fd=0; clinet_fd<=max_fd ; clinet_fd++){
            if(FD_ISSET(clinet_fd , &read_fds)){
                if(clinet_fd==0){
                    // input 
                }
                else if(clinet_fd!=socketfd){
                    unsigned char command[MAX_MSG_SIZE];
                    read(i, command, MAX_MSG_SIZE);
                    parse(command.c_str());
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
                    read(socket_accept_fd,buffer,MAX_MSG_SIZE);
                    //TODO check if user already exist
                    clients[socket_accept_fd] = buffer;
                    sprintf(buffer,"OK");
                    write(socket_accept_fd,buffer,strlen(buffer));
                    cout<<"new user "<< toUser[socket_accept_fd] << " connected!\n";
                }
            }
        }//for
    }//while

    return 0;
}
