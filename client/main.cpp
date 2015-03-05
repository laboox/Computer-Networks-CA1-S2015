/**
* File "main.cpp"
* Created by Sina on Sat Feb 28 17:47:50 2015.
*/

#include "register.h"
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

//TODO client can resive messages from server and show them or parse them
int main(){
    string order;
    vector<User> users;
    int sockfd = -1;
    char buffer[MAX_MSG_SIZE] = {};
    char port[] = CA_PORT;
    char ip[] = CA_IP;
    
    int caSockfd;
    try{
        connect(ip,port,&caSockfd);
        send_message("client", caSockfd);
        read(caSockfd, buffer, MAX_MSG_SIZE);
        if(strcmp("OK", buffer)){
            cout<<"connection failed!\n";
            return 1;
        }
        cout<<"connection to CA stablised!\n";
    }
    catch(exception& e){
        cout<<"connecting to CA failed!\n";
        return 1;
    }

    while(cin>>order){
        bzero(&buffer, MAX_MSG_SIZE);
        if(order=="Register"){
            string SSN, user, pass, repass;
            if(cin>>SSN>>user>>pass>>repass){
                if(pass!=repass){
                    cout<<"passwords does not match!\n";
                } else {
                    cout<<"registering user.\n";
                    int res = registerUser(SSN, user, pass, users, caSockfd);
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
        } else if(order=="Show" && cin>>order){
            if(order=="Candidates"){
                if(sockfd == -1){
                    cout<<"you'r not connected yet!\n";
                }else{
                    send_message("ShowCandidates",sockfd);
                    read(sockfd, buffer, MAX_MSG_SIZE);
                    cout<<buffer<<endl;
                }
            }
            else if(order=="Log"){
                string uname, pass;
                cin>>uname>>pass;
                if(uname!="Admin" || sockfd==-1 || pass!=ADMINPASS){
                    cout<<"you cant!\n";
                }else{
                    cout<<"getting log!\n";
                    send_message("ShowLog",sockfd);
                    read(sockfd, buffer, MAX_MSG_SIZE);
                    cout<<buffer<<endl;
                }
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
                    cout<<"start voting\n";
                    read(sockfd, buffer, MAX_MSG_SIZE);
                    if(!strcmp(buffer,"OK")){
                        send_message(uname,sockfd);
                        cout<<"uname OK\n";
                        read(sockfd, buffer, MAX_MSG_SIZE);
                        if(!strcmp(buffer,"OK")){
                            //encAndSend(sockfd, false, user->getCer(), user->getKP());
                            write(sockfd, user->encCer, user->encCerSize);
                            cout<<"checking certificate!\n";
                            read(sockfd, buffer, MAX_MSG_SIZE);
                            if(!strcmp(buffer, "OK")){
                                //encAndSend(sockfd, false, canNum, user->getKP());
                                send_message(canNum, sockfd);
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
        } 
        else if(order=="Disconnect"){
            string uname, pass;
            cin>>uname>>pass;
            if(uname!="Admin" || sockfd==-1 || pass!=ADMINPASS){
                cout<<"you cant!\n";
            }else{
                send_message("DC",sockfd);
                close(sockfd);
                sockfd = -1;
                cout<<"client disconnected\n";
            }
        }
        else{
            cout<<"Invalid Comand!\n";
        }   
    }
    return 0;
}
