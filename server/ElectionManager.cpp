#include "ElectionManager.h"

ElectionManager::ElectionManager(): start_time(0,0), end_time(23,59)
{
	//mkdir("./Candidates");
	//mkdir("./Boxes");	
}
	
void ElectionManager::addCandidate(string candidateName, int candidateCode)
{
    cout<<"Adding "<<candidateName<<" -> "<<candidateCode<<endl;
	if(candidateCodes.count(candidateCode)>0){
		throw Exeption("This candidate code has been added before.");
    }
	candidateCodes[candidateCode]=candidates.size();
	candidates.push_back(Candidate(candidateName, candidateCode));
}

void ElectionManager::showAllResults()
{
	cout<<"Voting Result"<<endl;
	for (int i = 0; i < boxes.size(); ++i)
	{
		cout<<"Box #"<<i<<"Result :"<<endl;
		vector<pii> votes=boxes[i].getVotes();
		for (int j = 0; j < votes.size(); ++j)
			cout<<candidates[candidateCodes[votes[j].CANDIDATE_CODE]].getName()<<" : "<<votes[j].CANDIDATE_VOTES<<endl;
	}
}
	
void ElectionManager::setVotingTime(Time start_time, Time end_time)
{
	if(! start_time.valid())
		cout<<"Invalid start_time"<<endl;
	if(! end_time.valid())
		cout<<"Invalid end_time"<<endl;
	if(! start_time.before(end_time))
		cout<<"Start_time must be before end_time"<<endl;
	this->start_time=start_time;
	this->end_time=end_time;
}
	
void ElectionManager::extendVotingTime(Time end_time)
{
	if(! end_time.valid())
		cout<<"Invalid end_time"<<endl;
	if(! this->end_time.before(end_time))
		cout<<"New end_time must be after previous end_time"<<endl;
	this->end_time=end_time;
}

string ElectionManager::showCandidates()
{
	string result="Candidates List: \n";
	for (int i = 0; i < candidates.size(); ++i)
		result+="Name : "+candidates[i].getName()+"\tCode : "+int2str(candidates[i].getCode())+"\n";
	result+="\n";
	return result;
}
	
string ElectionManager::showLog(int box_fd)
{
	string result="Voters List: \n";
	Box* box;
    for(int i=0;i<boxes.size();i++){
        if(boxes[i].getFD() == box_fd){
            box = &(boxes[i]);
        }
    }
	vector<string> voters=box->getVoters();
	for(int i=0; i<voters.size(); i++)
		result+=voters[i]+'\n';
	return result;
}

void ElectionManager::addBox(int fd)
{
	boxes.push_back(Box(fd));
}

void ElectionManager::parseServerCmd(string order)
{
	stringstream ss(order);
	string cmd;
	ss>>cmd;
    cout<<"doing "<<cmd<<endl;    
	if(cmd=="Add")
	{
		string param1, candidateName;
		int candidateCode;
		if(ss>>param1>>candidateName>>candidateCode && param1=="Candidate")
			addCandidate(candidateName, candidateCode);
		else
			throw Exeption("Invalid Command");
	}
	else if(cmd=="Show")
	{
		string param1,param2;
		if(ss>>param1>>param2 && param1=="All" && param2=="Results")
			showAllResults();
		else
			throw Exeption("Invalid Command");	
	}
	else if(cmd=="Set")
	{
		string param1,param2,time1,time2;
		if(ss>>param1>>param2>>time1>>time2 && param1=="Voting" && param2=="Time")
		{
			Time t1(time1);
			Time t2(time2);
			setVotingTime(t1, t2);
		}
		else
			throw Exeption("Invalid Command");

	}
	else if(cmd=="Extend")
	{
		string param1,param2,_time;
		if(ss>>param1>>param2>>_time && param1=="Voting" && param2=="Time")
		{
			Time t(_time);
			extendVotingTime(t);
		}
		else
			throw Exeption("Invalid Command");
	}
	else 
		throw Exeption("Invalid Command");
}

void ElectionManager::vote(string voter, int candidateCode, int box_fd)
{
	if(votedVoters.find(voter)!=votedVoters.end())
		throw Exeption(voter+" voted before.");
	if(candidateCodes.find(candidateCode)==candidateCodes.end())
		throw Exeption("Invalid candidate code.");
    votedVoters[voter]=true;
    for(int i=0;i<boxes.size();i++){
        if(boxes[i].getFD()==box_fd){
            boxes[i].vote(candidateCode, voter);
            break;
        }
    }
	candidates[candidateCodes[candidateCode]].incVote();
}


string ElectionManager::parseClientCmd(string order, int box_fd, int ca_fd)
{
    char buffer[MAX_MSG_SIZE] = {};     
    unsigned char* certif[MAX_MSG_SIZE] = {};
	stringstream ss(order);
	string cmd; ss>>cmd;
    cout<<"doing "<<cmd<<endl;
	if(cmd=="ShowLog")
		return showLog(box_fd);
	else if(cmd=="ShowCandidates")
		return showCandidates();
	else if(cmd=="Vote")
	{
        string voter;
        send_message("OK", box_fd);
        read(box_fd, buffer, MAX_MSG_SIZE);
        voter = buffer;
        send_message("OK", box_fd);
        int cerSize = read(box_fd, certif, MAX_MSG_SIZE);
        // ca check
        cout<<"checking cer with CA\n";
        send_message(voter, ca_fd);
        bzero(&buffer, MAX_MSG_SIZE);
        read(ca_fd, buffer, MAX_MSG_SIZE);
        if(strcmp(buffer,"OK")){
            send_message(buffer, box_fd);
            throw Exeption(buffer);
        }
        else {
            write(ca_fd,certif,cerSize);
            bzero(&buffer, MAX_MSG_SIZE);
            read(ca_fd, buffer, MAX_MSG_SIZE);
            if(strcmp(buffer,"OK")){
                send_message(buffer, box_fd);
                throw Exeption(buffer);
            } else {
                send_message("OK", box_fd);
                cout<<"certificate matches!\n";
            }
        }
        //ca check finish
        bzero(&buffer, MAX_MSG_SIZE);
        read(box_fd, buffer, MAX_MSG_SIZE);
        cout<<"want to vote: "<< buffer << endl;
        int canNum = atoi(buffer);
        try{
            vote(voter, canNum, box_fd);
            send_message("OK", box_fd);
        } catch (Exeption ex) {
            send_message(ex.getErr(), box_fd);
            throw ex;
        }
        cout<<"voting done!\n";
        return "";
	}
	else 
		throw Exeption("Invalid Command");
}
