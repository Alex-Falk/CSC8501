#pragma once
#include "Tournament.h"
class GangTournament :
	public Tournament
{
public:
	GangTournament(vector<string> files,char leaderChoice);
	~GangTournament();
	void runTournament();
	void readCombinationFile();
protected:
	char leaderChoice;
	vector<string> combinations;
};

