#pragma once
#include "Tournament.h"
class GangTournament :
	public Tournament
{
public:
	GangTournament(vector<string> files,char leaderChoice);
	~GangTournament();
	void runTournament();
protected:
	char leaderChoice;
};

