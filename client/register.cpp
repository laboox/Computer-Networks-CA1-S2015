/**
* File "register.cpp"
* Created by Sina on Sun Mar  1 16:08:26 2015.
*/

#include "register.h"
#define BUF_SIZE 256

int registerUser(string SSN, string user, string pass, vector<User>& users, int sockfd){
    cout<<"connecting to CA.\n";
    char buffer[MAX_MSG_SIZE];

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

    send_message(user, sockfd);
    read(sockfd,buffer,MAX_MSG_SIZE);
    //cout<<buffer<<endl;
    if(strcmp(buffer,"OK")){
        cout<<"err0: "<<buffer<<endl;
        return 0;
    }

    encAndSend(sockfd, false, msg, kp);
    bzero(&buffer,BUF_SIZE);

    //string ans = reciveAndDec(sockfd, false, kp);
    read(sockfd, buffer, MAX_MSG_SIZE);
    string ans = buffer;
    if(ans == "OK"){
        User nuser(user, pass, SSN);
        encAndSend(sockfd, false, "sendme", kp);
        bzero(&encMsg, MAX_MSG_SIZE);
        int encSize = read(sockfd, encMsg, MAX_MSG_SIZE);
        memcpy(nuser.encCer, encMsg, encSize);
        nuser.encCerSize = encSize;
        cout<<"certificate size: "<<encSize<<endl;
        nuser.setKP(kp);
        users.push_back(nuser);
        return 1;
    }
    else{
        cout<<"err1: "<<ans<<endl;
        return 0;
    }
    
    //cout<<kp.pub<<endl<<kp.priv<<endl;
}
