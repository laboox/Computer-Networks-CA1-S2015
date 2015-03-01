/**
* File "register.cpp"
* Created by Sina on Sun Mar  1 16:08:26 2015.
*/

#include "register.h"

int registerUser(string SSN, string user, string pass){
    cout<<"connecting to CA.\n";
    char port[] = CA_PORT;
    char ip[] = CA_IP;
    int sockfd;
    try{
        client_connect(ip,port,&sockfd);
        cout<<"connection stablised!\n";
    }
    catch(exception& e){
        cout<<"connecting failed!\n";
        return 1;
    }
}
