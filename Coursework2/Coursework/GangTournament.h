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
	void generateCombinations(int nrcombo);
	void printResults();
protected:
	char leaderChoice;
	int nrcombo;
	vector<string> combinations;
};

