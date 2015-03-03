/**
* File "register.cpp"
* Created by Sina on Sun Mar  1 16:08:26 2015.
*/

#include "register.h"
#define BUF_SIZE 256

int registerUser(string SSN, string user, string pass){
    cout<<"connecting to CA.\n";
    char port[] = CA_PORT;
    char ip[] = CA_IP;
    char buffer[BUF_SIZE];

    int sockfd;
    try{
        connect(ip,port,&sockfd);
        cout<<"connection stablised!\n";
    }
    catch(exception& e){
        cout<<"connecting failed!\n";
        return 1;
    }
    write(sockfd,user.c_str(),user.size()+1);
    read(sockfd,buffer,BUF_SIZE);
    //cout<<buffer<<endl;
    if(strcmp(buffer,"OK")){
        cout<<buffer<<endl;
        return 1;
    }
    string addr;
    addr += "../users/"+user+"_pub.pem"; 
    cout<<"generating key pairs.\n";
    ofstream pubWriter(addr.c_str(), std::ofstream::out);
    KeyPair kp = getKeyPair(2048);
    pubWriter<<kp.pub;
    pubWriter.close();
    cout<<"public key writed to file.\n";
    RSA* rsa = createRSA(kp.pub.c_str(),true);
    cout<<"rsa creation: "<<rsa<<endl;
    unsigned char encMsg[MAX_MSG_SIZE];
    string msg = SSN+" "+user+" "+pass;
    cout<<"encrypting "<<msg<<endl;
    int encSize = private_encrypt(msg, kp.priv.c_str(), encMsg);
    cout<<"encrypting finished.\n";
    write(sockfd, encMsg, encSize);
    bzero(&buffer,BUF_SIZE);
    encSize = read(sockfd,buffer,BUF_SIZE);
    string ans = private_decrypt((unsigned char*)buffer, encSize, (const char*)kp.priv.c_str());
    if(ans == "OK"){
        encAndSend(sockfd, false, "sendme", kp);
    }
    else{
        cout<<ans<<endl;
        return 0;
    }
    
    //cout<<kp.pub<<endl<<kp.priv<<endl;
}
