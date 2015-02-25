/**
* File "Candidate.h"
* Created by Sina on Wed Feb 25 14:26:08 2015.
*/

#pragma once

#include "Header.h"

#define path "candidates/"

class Candidate{
private:
    string name;
    int num;
    int votes;

public:
    Candidate ( string, int );
    void save ();
    void incVote();
    void setVote (int);
    int getVote ();
};
