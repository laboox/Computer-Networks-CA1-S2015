#pragma once

#include "Header.h"
#include "Box.h"
#include "Candidate.h"
#include "Time.h"

#define BOX_FD first
#define BOX_INDEX second

class ElectionManager{
private:
    vector<Candidate> candidates;
    vector<Box> boxes;
    map<int, int> box_fds;
    map<string, bool> votedVoters;
    map<int, int> candidateCodes;
    Time start_time;
    Time end_time;
public:
	ElectionManager();
	void addCandidate(string candidateName, int candidateCode);
	void showAllResults();
	void setVotingTime(Time start_time, Time end_Time);
	void extendVotingTime(Time end_Time);

	void addBox(int fd);
	
	string showCandidates();
    void vote(string voter, int candidateCode, int box_fd);
	string showLog(int box_fd);

	void parseServerCmd(string order);
	string parseClientCmd(string order, int box_fd, int ca_fd);
};

