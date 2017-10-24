#pragma once
#include "Game.h"
class Tournament
{
public:
	struct result {
		string name = "";
		int total = 0;
		vector<int> sentences = {};
	};

	Tournament(vector<string> files);
	~Tournament();
	void runTournament();													// Runs the tournament with the given files
	result findWinner();													// Returns the strategy that has the lowest cumulative sentence
	void printResults();													// Prints the results out in the console
	void saveResults(string filename);
	void setFilenames(vector<string> names) { filenames = names; };			// Takes a vector of filenames in order to use them as a list of strategies to use in the tournament
private:
	vector<string> filenames; // = { "test.txt","test2.txt" };
	vector<result> results;



};

