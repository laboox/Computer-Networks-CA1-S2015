/**
* File "Candidate.h"
* Created by Sina on Wed Feb 25 14:26:08 2015.
*/

#pragma once

#include "Header.h"

#define path "Candidates/"

class Candidate{
private:
    string name;
    int code;
    int votes;

public:
    Candidate (string name, int code);
    void save ();
    void incVote();
    int getVote ();
    int getCode();
    string getName();
};
