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
	void runTournament(string filename, Settings * settings);																	// Runs the tournament with the given files (from instantiation)
	ostream& printFull(GangGame * game,int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream& ostr);	// Print out the full detail of the game with outcomes, sentences and spy results
	ostream & printHalf(GangGame * game, int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream & ostr);	// Only print the sentences of each game
	void readCombinationFile();								// Read in a file that stores a list of strategy combinations to use
	void generateCombinations(int nrcombo);					// Generate a number of combinations and write them to a file
	void printResults();									// Print out the final total sentences for each strategy combination
	void printResults_toFile(string filename);				// Print out the final total sentences for each strategy combination and the winning combination to a file
protected:
	char leaderChoice;
	int nrcombo;
	vector<string> combinations;
};

