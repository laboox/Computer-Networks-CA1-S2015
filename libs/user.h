/**
* File "user.h"
* Created by Sina on Tue Mar  3 17:22:55 2015.
*/

#pragma once

#include "Header.h"

class User{
private:
    string uname;
    string pass;
    string SSN;
    string cer;
    KeyPair kp;
public:
    User(string Uname, string Pass, string sSN): uname(Uname), pass(Pass), SSN(sSN) {}
    User(string msg);
    string getUname() { return uname; }
    string getSSN () { return SSN; }
    string getPass() { return pass; }
    string getCer();
    bool checkCer(string cmp) { return cer==cmp; }
    void setCer(string Cer) { cer = Cer; }
    void setKP(const KeyPair& KP) { kp = KP; }
    KeyPair getKP() { return kp; }
};

bool isUserExist(vector<User>& users, User user);
