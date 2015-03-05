#include "ElectionManager.h"

ElectionManager();
{
	start_time = new Time(0,0);
	end_Time = new Time(23,59);
	mkdir("./Candidates");
	mkdir("./Boxes");	
}
	
void ElectionManager::addCandidate(string candidateName, int candidateCode)
{
	if(candidateCodes.find(candidateCode)==candidateCodes.end())
			throw(new Exeption("This candidate code has been added before."));
	candidateCodes[candidateCode]=candidates.size();
	candidates.push_back(new Candidate(candidateName, candidateCode));
}

string ElectionManager::showAllResults()
{
	cout<<"Voting Result"<<endl;
	for (int i = 0; i < boxes.size(); ++i)
	{
		cout<<"Box #"<<i<<"Result :"<<endl;
		vector<pii> votes=boxes[i].getVotes();
		for (int j = 0; j < votes.size(); ++j)
			cout<<candidate[candidateCodes[votes[j].CANDIDATE_CODE]].getName()<<" : "<<votes[j].CANDIDATE_VOTES)<<endl;
		return result;
	}
}
	
void ElectionManager::setVotingTime(Time start_time, Time end_Time)
{
	if(! valid(start_time))
		cout<<"Invalid start_time"<<endl;
	if(! valid(end_time))
		cout<<"Invalid end_time"<<endl;
	if(! before(start_time, end_Time))
		cout<<"Start_time must be before end_time"<<endl;
	this.start_time=start_time;
	this.end_Time=end_Time;
}
	
void ElectionManager::extendVotingTime(Time end_Time)
{
	if(! valid(end_time))
		cout<<"Invalid end_time"<<endl;
	if(! before(this.end_Time, end_Time))
		cout<<"New end_time must be after previous end_time"<<endl;
	this.end_Time=end_Time;
}

string ElectionManager::showCandidates()
{
	string result="Candidates List"<<endl;
	for (int i = 0; i < candidates.size(); ++i)
		result+="Name : "+candidates[i].getName()+"\tCode : "+int2str(candidates[i].getCode)())<<endl;
	result+="\n";
	return result;
}
	
void ElectionManager::vote(string voter, int candidateCode, int box_fd, 
	const unsigned char* certifacate, int certifacate_size)
{
	/*
		check certificate with CA
	*/
	if(votedVoters.find(voter)!=votedVoters.end())
		throw new Exeption(voter+" voted before.");
	if(candidateCodes.find(candidateCode)==candidateCodes.end())
		throw new Exeption("Invalid candidate code.");
	votedVoters[voter]=true;
	boxes[box_fd].vote(candidateCode, voter);
	candidates[candidateCodes[candidateCode]].incVote();
}

string ElectionManager::showLog(int box_fd);
{
	string result="Voters List :";
	Box box=boxes[box_fds[box_fd]];
	vector<string> voters=box.getVoters();
	for(int i=0; i<voters.size(); i++)
		result+=Voters[i]+'\n';
	return result;
}

void ElectionManager::addBox(int fd)
{
	boxes.push_back(new Box(fd));
}
