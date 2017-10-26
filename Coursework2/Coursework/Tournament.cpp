#include "Tournament.h"
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;


Tournament::Tournament(vector<string> files, char display)
{
	filenames = files;
	results.resize(filenames.size());
	DISPLAY = display;
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
				
				Game * game = new Game(filenames[i],filenames[j]);
				game->run(200);													// 200 Iterations for a given game
				Matrix<int> * game_results = game->getResults();

				results[j].name = filenames[j];
				results[j].sentences.resize(filenames.size());

				results[i].sentences[j] = game_results->get_element(4,0);
				results[j].sentences[i] = game_results->get_element(4,1);
				
				switch (DISPLAY)
				{
				case 'A':
					cout << filenames[i] << " vs. " << filenames[j] << "\n";
					cout << "A: w:" << game_results->get_element(0, 0) << " x:" << game_results->get_element(1, 0) << " y:" << game_results->get_element(2, 0) << " z:" << game_results->get_element(3, 0) << " sentence:" << game_results->get_element(4, 0) << "\n";
					cout << "B: w:" << game_results->get_element(0, 1) << " x:" << game_results->get_element(1, 1) << " y:" << game_results->get_element(2, 1) << " z:" << game_results->get_element(3, 1) << " sentence:" << game_results->get_element(4, 1) << "\n";
					cout << "\n";
					break;
				case 'B':
					cout << filenames[i] << " vs. " << filenames[j] << "\n";
					cout << "A: sentence: " << game_results->get_element(4, 0) << "\n";
					cout << "B: sentence: " << game_results->get_element(4, 1) << "\n";
					cout << "\n";
					break;
				}

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


