#pragma once
#include "Tournament.h"
class GangTournament :
	public Tournament
{
public:
	GangTournament(vector<string> files);
	~GangTournament();
	void runTournament();
};

