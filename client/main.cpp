/**
* File "main.cpp"
* Created by Sina on Sat Feb 28 17:47:50 2015.
*/

#include "register.h"
#include "user.h"

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
    vector<user> users;
    User* user;

    while(cin>>order){
        if(order=="Register"){
            string SSN, user, pass, repass;
            if(cin>>SSN>>user>>pass>>repass){
                if(pass!=repass){
                    cout<<"passwords does not match!\n";
                }else{
                    cout<<"registering user.\n";
                    registerUser(SSN, user, pass, users);
                }
            }else{
                cout<<"wronge input!\n";
            }
        } else if(order=="Connect" && cin>>order && order=="Server"){
            int serverPort;
            string uname;
            cin>>serverPort>>uname;
            if(uname=="Admin" || regUser(uname, users)){
                //TODO do sth for Admin
                user = getUser(uname, users);
                //TODO connect user to server 
            }else{
                cout<<"you didn't registered from this client!\n";
            }
        } else if(order=="Show" && cin>>order && order=="Candidate"){
            if(user==null){
                cout<<"you'r not connected yet!\n";
            }else{
            }
        } else if(order=="Vote"){
            if(user==null){
                cout<<"you'r not connected yet!\n";
            }else{
            }
        } else if(order=="Show" && cin>>order && order=="Log"){
            if(user==null || user->getUname()!="Admin"){
                cout<<"you'r not connected yet!\n";
            }else{
            }
        }
    }
    return 0;
}
