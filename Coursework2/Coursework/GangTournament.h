#pragma once
#include "Tournament.h"
#include "Matrix.h"
#include "GangGame.h"
#include <fstream>


using namespace std;

class GangTournament :
	public Tournament
{
public:
	GangTournament(vector<string> files,char leaderChoice, char display);
	~GangTournament();
	void runTournament(string filename, Settings * settings);
	ostream& printFull(GangGame * game,int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream& ostr);
	ostream & printHalf(GangGame * game, int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream & ostr);
	void readCombinationFile();
	void generateCombinations(int nrcombo);
	void printResults();
	void printResults_toFile(string filename);
protected:
	char leaderChoice;
	int nrcombo;
	vector<string> combinations;
};

