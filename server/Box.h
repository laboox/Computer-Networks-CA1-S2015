#pragma once

#include "Header.h"

class Box{
private:
    int fileDescriptor;
    vector<pii> votes;
    vector<string> voters;
    map<int, int> candidateCodes;

public:
    Box (int fd) : fileDescriptor(fd) {}
    void save ();
    void vote(int candidateCode, string voter);
    int getVote (int candidateCode);
    vector<pii> getVotes ();
    vector<string> getVoters();
    int getFD() { return fileDescriptor; }
};


string int2str(int n);
