#pragma once
#include "Game.h"
#include "Matrix.h"
#include "GlobalFunctions.h"
class Tournament
{
public:
	virtual struct result {
		string name = "";
		int total = 0;
		vector<int> sentences = {};
	};

	Tournament(vector<string> files,char Display);
	~Tournament();
	virtual void runTournament(string filename,Settings * settings);				// Runs the tournament with the given files
	virtual result findWinner();													// Returns the strategy that has the lowest cumulative sentence
	virtual void printResults();													// Prints the results out in the console
	virtual void printResults_toFile(string filename);
	virtual void setFilenames(vector<string> names) { filenames = names; };			// Takes a vector of filenames in order to use them as a list of strategies to use in the tournament
protected:
	vector<string> filenames;
	vector<result> results;
	Matrix<result> MatrixResults;
	char DISPLAY;



};

