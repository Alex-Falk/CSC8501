#include "Tournament.h"
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;


Tournament::Tournament(vector<string> files)
{
	filenames = files;
	results.resize(filenames.size());
}


Tournament::~Tournament() {
}


void Tournament::runTournament()												// Runs the tournament with the given files (from instantiation)
{
	for (int i = 0; i < filenames.size(); ++i)
	{
		int totalA = 0, totalB = 0;
		results[i].name = filenames[i];
		results[i].sentences.resize(filenames.size());

		for (int j = i; j < filenames.size(); ++j) 
		{
			if (i != j)															// Prevents Strategies from playing themselves
			{
				cout << filenames[i] << " vs. " << filenames[j] << "\n";		
				Game * game = new Game(filenames[i],filenames[j]);
				game->run(200);													// 200 Iterations for a given game
				vector<int> game_results = game->getResults();

				results[j].name = filenames[j];
				results[j].sentences.resize(filenames.size());

				results[i].sentences[j] = game_results[0];
				results[j].sentences[i] = game_results[1];
				
				cout << "\n";

				delete game;
			}
		}
		for (int k = 0; k < results.size(); ++k)								
		{	// Count final scores for each strategy
			results[k].total = std::accumulate(results[k].sentences.begin(), results[k].sentences.end(), 0);
		}
	}
}

void Tournament::printResults()													
{	// Prints the final total scores out in the console
	for (int i = 0; i < results.size(); ++i) 
	{
		cout << filenames[i] << "\t";
		cout << results[i].total << "\n";
	}
}

Tournament::result Tournament::findWinner()									
{	// Iterates through the results to find the strategy with the lowest score
	result winner = results[0];
	for (int i = 0; i < results.size(); ++i) 
	{
		if (results[i].total < winner.total) 
		{
			winner = results[i];
		}
	}
	return winner;
}


