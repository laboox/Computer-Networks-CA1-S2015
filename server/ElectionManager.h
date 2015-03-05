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
    vector<Boxes> boxes;
    map<int, int> box_fds;
    map<string, bool> votedVoters;
    map<int, int> candidateCodes;
    Time start_time;
    Time end_Time;
public:
	ElectionManager();
	void addCandidate(string candidateName, int candidateCode);
	void showAllResults();
	void setVotingTime(Time start_time, Time end_Time);
	void extendVotingTime(Time end_Time);

	void addBox(int fd);
	
	string showCandidates();
	void vote(string username, int candidateCode);
	string showLog();

	void parseServerCmd(string order);
	string parseClientCmd(string order, int box_fd);
};

