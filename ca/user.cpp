/**
* File "user.cpp"
* Created by Sina on Tue Mar  3 17:22:52 2015.
*/

#include "user.h"

bool isUserExist(vector<User>& users, User user){
    for(int i=0;i<users.size();i++){
        if(users[i].getUname() == user.getUname() || users[i].getSSN() == user.getSSN()){
            return false;
        }
    }
    return true;
}

User::User(string msg){
    stringstream ss(msg);
    ss>>SSN>>uname>>pass;
}
