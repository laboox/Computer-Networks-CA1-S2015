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

    ElectionManager em = new ElectionManager();
    /* connect to ca*/
    while(1){
        read_fds = server;
        if(select(max_fd+1,&read_fds,NULL,NULL,NULL) < 0)
            failure("problem in sockets select!");
        int box_fd;
        for( box_fd=0; box_fd<=max_fd ; box_fd++){
            if(FD_ISSET(box_fd , &read_fds)){
                if(box_fd==0){
                    string order;
                    getline(cin, order);
                    parse(order);
                }
                else if(box_fd!=socketfd){
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
                    cout<<"new election center connected.\n";
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
