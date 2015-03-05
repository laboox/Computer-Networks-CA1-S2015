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
	if(! start_time.valid())
		cout<<"Invalid start_time"<<endl;
	if(! end_time.valid())
		cout<<"Invalid end_time"<<endl;
	if(! start_time.before(end_Time))
		cout<<"Start_time must be before end_time"<<endl;
	this->start_time=start_time;
	this->end_Time=end_Time;
}
	
void ElectionManager::extendVotingTime(Time end_Time)
{
	if(! end_time.valid())
		cout<<"Invalid end_time"<<endl;
	if(! this->end_Time.before(end_Time))
		cout<<"New end_time must be after previous end_time"<<endl;
	this->end_Time=end_Time;
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

void ElectionManager::parseServerCmd(string order)
{
	stringstream ss(order);
	string cmd;
	ss>>cmd;
	if(cmd=="Add")
	{
		string param1, candidateName;
		int candidateCode;
		if(ss>>param1>>candidateName>>candidateCode && param1=="Candidate")
			addCandidate(candidateName, candidateCode);
		else
			throw new Exeption("Invalid Command");
	}
	else if(cmd=="Show")
	{
		string param1,param2;
		if(ss>>param1>>param2 && param1=="All" && param2=="Results")
			showAllResults();
		else
			throw new Exeption("Invalid Command");	
	}
	else if(cmd=="Set")
	{
		string param1,param2,time1,time2;
		if(ss>>param1>>param2>>time1>>time2 && param1=="Voting" && param2=="Time")
		{
			Time t1=new Time(time1);
			Time t2=new Time(time2);
			setVotingTime(t1, t2);
		}
		else
			throw new Exeption("Invalid Command");

	}
	else if(cmd=="Extend")
	{
		string param1,param2,_time;
		if(ss>>param1>>param2>>_time && param1=="Voting" && param2=="Time")
		{
			Time t=new Time(_time);
			extendVotingTime(t);
		}
		else
			throw new Exeption("Invalid Command");
	}
	else 
		throw new Exeption("Invalid Command")
}

void ElectionManager::parseClientCmd(string order, int box_fd)
{
	stringstream ss(order);
	string cmd; ss>>cmd;
	if(cmd=="ShowLog")
		return ShowLog(box_fd);
	else if(cmd=="ShowCandidates")
		return ShowCandidates();
	else if(cmd=="Vote")
	{

	}
	else 
		throw new Exeption("Invalid Command")
}
