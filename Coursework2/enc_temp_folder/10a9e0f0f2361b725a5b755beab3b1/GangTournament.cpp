#include "GangTournament.h"
#include "GlobalFunctions.h"
#include "GangGame.h"
#include "Gang.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;


GangTournament::GangTournament(vector<string> files, char leaderchoice, char display) : Tournament(files, display), leaderChoice(leaderchoice)
{
}


GangTournament::~GangTournament()
{
}

void GangTournament::runTournament()
{
	for (int i = 0; i < combinations.size(); ++i)
	{
		int totalA = 0, totalB = 0;
		results[i].name = combinations[i];
		results[i].sentences.resize(combinations.size());

		for (int j = i; j < combinations.size(); j++)
		{
			GangGame * game = new GangGame(combinations[i], combinations[j]);

			method mthd = method::RANDOM;
			switch (leaderChoice)
			{
			case 'A':
				mthd == method::CUSTOM;
			case 'B':
				mthd == method::SWAP;
			case 'C':
				mthd == method::STAY;
			case 'D':
				mthd == method::RANDOM;
			}

			cout << "Game " << i + 1 << "\n";

			game->run(200, mthd);

			Matrix<int> * game_results = game->getResults();

			results[j].name = combinations[j];
			results[j].sentences.resize(combinations.size());

			results[i].sentences[j] = game_results->get_element(7, 0);
			results[j].sentences[i] = game_results->get_element(7, 1);

			switch (DISPLAY)
			{
			case 'A':
				cout << "\n" << *(game->getGangA()) << "\n" << "vs.\n" << *(game->getgangB()) << "\n\n";
				cout << "A: w:" << game_results->get_element(0, 0) << " x:" << game_results->get_element(1, 0) << " y:" << game_results->get_element(2, 0) << " z:" << game_results->get_element(3, 0) 
					<< " a:" << game_results->get_element(4, 0) << " b:" << game_results->get_element(5, 0) << " c:" << game_results->get_element(6, 0) << " sentence:" << game_results->get_element(7, 0) << "\n";
				cout << "B: w:" << game_results->get_element(0, 1) << " x:" << game_results->get_element(1, 1) << " y:" << game_results->get_element(2, 1) << " z:" << game_results->get_element(3, 1) 
					<< " a:" << game_results->get_element(4, 1) << " b:" << game_results->get_element(5, 1) << " c:" << game_results->get_element(6, 1) << " sentence:" << game_results->get_element(7, 1) << "\n"; ;
				break;
			case 'B':
				cout << "\n" << *(game->getGangA()) << "\n" << "vs.\n" << *(game->getgangB()) << "\n\n";
				cout << "A: sentence: " << game_results->get_element(7, 0) << "\n";
				cout << "B: sentence: " << game_results->get_element(7, 1) << "\n";
				break;
				
			}

			delete game;
		}

		for (int k = 0; k < results.size(); ++k)
		{	// Count final scores for each strategy
			results[k].total = std::accumulate(results[k].sentences.begin(), results[k].sentences.end(), 0);
		}

	}
}

void GangTournament::readCombinationFile()
{
	ifstream inFile;
	inFile.open("StrategyCombinations.txt");

	while (!inFile.eof()) {
		string line;
		getline(inFile, line);
		combinations.push_back(line);
	}

	inFile.close();

	results.resize(combinations.size());

	cout << combinations.size() << " combinations found and read in \n";
}

void GangTournament::generateCombinations(int nrcombo)
{
	ofstream outFile;
	outFile.open("StrategyCombinations.txt");

	for (int i = 0; i < nrcombo; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			outFile << filenames[rand() % filenames.size()];
			if (j != 4) { outFile << " "; }
		}
		if (i != nrcombo - 1) { outFile << "\n"; }
	}

	outFile.close();
}

void GangTournament::printResults()
{

	for (int i = 0; i < results.size(); ++i)
	{
		cout << "Combination of strategies: ";

		cout << shortenStrategyList(results[i].name) << "\t"  ;
		cout << results[i].total << "\n";
	}

}