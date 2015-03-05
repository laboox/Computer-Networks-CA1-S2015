/**
* File "Candidate.cpp"
* Created by Sina on Wed Feb 25 14:26:05 2015.
*/

#include "Candidate.h"

Candidate::Candidate (string name, int code) {
    this.name = name;
    this.code = code;
    votes = 0;
}

void Candidate::save () {
    string addr = path + name + ".txt";
    ifstream file(addr);
    file<<name<<endl;
    file<<code<<endl;
    file<<votes<<endl;
    file.close();
}


void Candidate::incVote () {
    vote++;
}

int Candidate::getVote () {
    return vote;
}

int Candidate::getCode () {
    return code;
}

int Candidate::setVote (int vote) {
    this.vote = vote;
}


