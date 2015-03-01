/**
* File "main.cpp"
* Created by Sina on Sat Feb 28 17:47:50 2015.
*/

#include "Header.h"
#include "register.h"

int main(){
    string order;
    while(cin>>order){
        if(order=="Register"){
            string SSN, user, pass, repass;
            if(cin>>SSN>>user>>pass>>repass){
                if(pass!=repass){
                    cout<<"passwords does not match!\n";
                }else{
                    cout<<"registering user.\n";
                    registerUser(SSN, user, pass);
                }
            }else{
                cout<<"wronge input!\n";
            }
        }
    }
    return 0;
}
