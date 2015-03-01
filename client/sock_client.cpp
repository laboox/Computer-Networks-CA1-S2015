#include "sock_client.h"

class ServerNotFound: public exception {} ServerNotFoundEx;
class PortNotFound: public exception {} PortNotFoundEx;
class Connection: public exception {} ConnectionEx;
class TooLong: public exception {} TooLongEx;

void client_connect(char* ip, char* port, int* socketfd){
	int port_number, char_number;
	struct sockaddr_in server_address;
	struct hostent *server;

	port_number = atoi(port);
	*socketfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &server_address, sizeof(server_address));
	if (*socketfd < 0) 
		throw ServerNotFoundEx;
	server = gethostbyname(ip);
	if (server == 0)
		throw PortNotFoundEx;
	server_address.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr,server->h_length);
	server_address.sin_port = htons(port_number);
	if (connect(*socketfd,(struct sockaddr *)&server_address,sizeof(server_address)) == -1) 
		throw ConnectionEx;
}

void send_message(string message, int sockfd){
    string buff;
    buff = message+"\n";
    if(buff.size()>MAX_BUFFER_SIZE)
        throw TooLongEx;
    int nwrite = write(sockfd, buff.c_str(), MAX_BUFFER_SIZE);
    if(nwrite<=0){
        throw ConnectionEx;
    }
}
