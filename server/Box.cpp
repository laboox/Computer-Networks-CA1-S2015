
#include "Box.h"

void Box::save () {
    string addr = path + fileDescriptor + ".txt";
    ifstream file(addr);
    for (int i = 0; i < votes.size(); i++)
    {
    	file<<votes[i].CANDIDATE_CODE<<endl;
    	file<<votes[i].CANDIDATE_VOTES<<endl;
    }
    file.close();
}

void Box::vote(int candidateCode)
{
	if(candidateCodes[candidateCode]==0)
	{
		candidateCodes[candidateCode]=votes.size();
		votes.push_back(pii(candidateCode, 1));
	}
	else
		votes[candidateCodes[candidateCode]]++;

	
}

void Box::getVote (int candidateCode)
{
	return votes[candidateCodes[candidateCode]];
}

vector<pii> Box::getVotes ()
{
	return votes;
}

vector<string> Box::getVoters()
{
	return voters;
}