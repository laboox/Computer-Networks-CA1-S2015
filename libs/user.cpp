/**
* File "user.cpp"
* Created by Sina on Tue Mar  3 17:22:52 2015.
*/

#include "user.h"

bool isUserExist(vector<User>& users, User user){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname() == user.getUname() || users[i].getSSN() == user.getSSN() || user.getUname() == "Admin"){
            return true;
        }
    }
    return false;
}

bool isUserExist(vector<User>& users, string uname){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname() == uname){
            return true;
        }
    }
    return false;
}

User& findUser(vector<User>& users, string uname){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname() == uname)
            return users[i];
    }
}

User::User(string msg){
    stringstream ss(msg);
    ss>>SSN>>uname>>pass;
}

string User::getCer(){
    if(cer==""){
        time_t rawtime;
        struct tm * timeinfo;
        stringstream ret;

        time(&rawtime);
        timeinfo = localtime (&rawtime);
        
        ret<<uname<<endl<<pass<<endl<<SSN<<endl<<timeinfo->tm_hour;

        cer = ret.str();
        return ret.str();
    }
    else{
        return cer;
    }
}
