/**
* File "Candidate.cpp"
* Created by Sina on Wed Feb 25 14:26:05 2015.
*/

#include "Candidate.h"

Candidate::Candidate (string Name, int Num){
    name = Name;
    num = Num;
    votes = 0;
}

void Candidate::save () {
    string addr = path + name + ".txt";
    ifstream file(addr);
    file<<name<<endl;
    file<<num<<endl;
    file<<vote<<endl;
    file.close();
}

void Candidate::incVote () {
    vote++;
}

int Candidate::getVote () {
    return vote;
}

int Candidate::setVote (int Vote) {
    vote = Vote;
}
