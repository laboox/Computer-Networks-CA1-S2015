/**
* File "main.cpp"
* Created by Sina on Sat Feb 28 17:47:50 2015.
*/

#include "register.h"
#include "user.h"
#define ADMINPASS "123456"

bool regUser(string uname, vector<User>& users){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname()== uname)
            return true;
    }
    return false;
}

User* getUser(string uname, vector<User>& users){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname()== uname)
            return &(users[i]);
    }
    return NULL;
}

int main(){
    string order;
    vector<User> users;
    int sockfd = -1;
    char buffer[MAX_MSG_SIZE] = {};

    while(cin>>order){
        bzero(&buffer, MAX_MSG_SIZE);
        if(order=="Register"){
            string SSN, user, pass, repass;
            if(cin>>SSN>>user>>pass>>repass){
                if(pass!=repass){
                    cout<<"passwords does not match!\n";
                }else{
                    cout<<"registering user.\n";
                    int res = registerUser(SSN, user, pass, users);
                    if(res){
                        cout<<"user registered successfully.\n";
                    }else{
                        cout<<"failed to register user!\n";
                    }
                }
            }else{
                cout<<"wronge input!\n";
            }
        } else if(order=="Connect" && cin>>order && order=="Server"){
            int serverPort;
            string uname;
            cin>>serverPort>>uname;
            if(uname=="Admin" && sockfd==-1){
                try{
                    connect(SERVER_IP,SERVER_PORT,&sockfd);
                    cout<<"connection stablised!\n";
                }
                catch(exception& e){
                    cout<<"connecting failed!\n";
                    sockfd = -1;
                }
            }else if(sockfd!=-1){
                cout<<"you already connected!\n";
            }else{
                cout<<"you'r not Admin!\n";
            }
        } else if(order=="Show" && cin>>order && order=="Candidate"){
            if(sockfd == -1){
                cout<<"you'r not connected yet!\n";
            }else{
                send_message("ShowCandidate",sockfd);
                read(sockfd, buffer, MAX_MSG_SIZE);
                cout<<buffer<<endl;
            }
        } else if(order=="Vote"){
            string uname;
            string canNum;
            cin>>uname>>canNum;
            if(sockfd==-1){
                cout<<"you'r not connected yet!\n";
            }else{
                if(regUser(uname, users)){
                    User* user = getUser(uname, users);
                    send_message("Vote",sockfd);
                    read(sockfd, buffer, MAX_MSG_SIZE);
                    if(!strcmp(buffer,"OK")){
                        send_message(uname,sockfd);
                        read(sockfd, buffer, MAX_MSG_SIZE);
                        if(!strcmp(buffer,"OK")){
                            encAndSend(sockfd, false, user->getCer(), user->getKP());
                            read(sockfd, buffer, MAX_MSG_SIZE);
                            if(!strcmp(buffer, "OK")){
                                encAndSend(sockfd, false, canNum, user->getKP());
                                read(sockfd, buffer, MAX_MSG_SIZE);
                                if(!strcmp(buffer, "OK")){
                                    cout<<"vote submitted!\n";
                                }else{
                                    cout<<buffer<<endl;
                                }
                            } else {
                                cout<<"something went wrong.\n";
                            }
                        } else {
                            cout<<"something went wrong.\n";
                        }

                    }else{
                        cout<<"something went wrong.\n";
                    }
                }else{
                    cout<<"you'r not registered with this client.\n";
                }
            }
        } else if(order=="Show" && cin>>order && order=="Log"){
            string uname, pass;
            cin>>uname>>pass;
            if(uname!="Admin" || sockfd==-1 || pass!=ADMINPASS){
                cout<<"you cant!\n";
            }else{
                send_message("ShowLog",sockfd);
                read(sockfd, buffer, MAX_MSG_SIZE);
                cout<<buffer<<endl;
            }
        } else if(order=="Disconnect"){
            string uname, pass;
            cin>>uname>>pass;
            if(uname!="Admin" || sockfd==-1 || pass!=ADMINPASS){
                cout<<"you cant!\n";
            }else{
                send_message("DC",sockfd);
                close(sockfd);
                sockfd = -1;
            }
        }
    }
    return 0;
}
