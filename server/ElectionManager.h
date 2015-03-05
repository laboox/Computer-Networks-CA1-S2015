#pragma once

#include "Header.h"

class ElectionManager{
private:
    vector<Candidate> candidates;
    vector<Boxes> boxes;
    map<string, bool> votedVoters;
    map<int, string> candidateCodes;
    Time start_time;
    Time end_Time;
public:
	ElectionManager();
	void addCandidate(string candidateName, int candidateCode);
	string showAllResults();
	void setVotingTime(Time start_time, Time end_Time);
	void extendVotingTime(Time end_Time);

	void addBox(int fd);
	string showCandidates();
	void vote(string username, int candidateCode);
	string showLog();
};
