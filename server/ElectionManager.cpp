#include "ElectionManager.h"

ElectionManager();
{
	/* defaults
	start_time = 
	end_Time = 
	*/

}
	
void ElectionManager::addCandidate(string candidateName, int candidateCode)
{
	if(candidateCodes.find(candidateCode)==candidateCodes.end())
			throw(new Exeption("This candidate code has been added before."));
	candidates.push_back(new Candidate(candidateName, candidateCode));
	candidateCodes[candidateCode]=candidateName;
}

string ElectionManager::showAllResults()
{
	streing result="Voting Result\n";
	for (int i = 0; i < boxes.size(); ++i)
	{
		result+="Box #"+int2str(i)+"Result :\n";
		vector<pii> votes=boxes[i].getVotes();
		for (int j = 0; j < votes.size(); ++j)
			result+=candidateCodes[votes[j].CANDIDATE_CODE]+" : "+int2str(votes[j].CANDIDATE_VOTES)+"\n";
		return result;
	}
}
	setVotingTime(Time start_time, Time end_Time);
	extendVotingTime(Time end_Time);

	showCandidates();
	vote(string username, int candidateCode);
	showLog();