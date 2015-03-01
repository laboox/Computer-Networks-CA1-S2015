#ifndef SIAH_SERVER
#define SIAH_SERVER

#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "Header.h"


#define MAX_CLIENT 5

void failure(string);
void build_server(int socketfd, struct sockaddr_in *server_address, int port_number);

#endif
