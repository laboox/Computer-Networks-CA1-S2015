#include "Box.h"

void Box::save () {
    string addr=path + int2str(fileDescriptor) + ".txt";
    ofstream file(addr.c_str(), std::ofstream::out);
    for (int i = 0; i < votes.size(); i++)
    {
    	file<<votes[i].CANDIDATE_CODE<<endl;
    	file<<votes[i].CANDIDATE_VOTES<<endl;
    }
    file.close();
}

void Box::vote(int candidateCode, string voter)
{
	if(candidateCodes[candidateCode]==0)
	{
		candidateCodes[candidateCode]=votes.size();
		votes.push_back(pii(candidateCode, 1));
	}
	else
		votes[candidateCodes[candidateCode]].CANDIDATE_VOTES++;
	voters.push_back(voter);
	save();
}

int Box::getVote (int candidateCode)
{
	return votes[candidateCodes[candidateCode]].CANDIDATE_VOTES;
}

vector<pii> Box::getVotes ()
{
	return votes;
}

vector<string> Box::getVoters()
{
	return voters;
}

string int2str(int n)
{
	stringstream s;
	s<<n;
	return s.str();
}
