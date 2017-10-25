#include "GangTournament.h"
#include "GlobalFunctions.h"
#include "GangGame.h"
#include "Gang.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;


GangTournament::GangTournament(vector<string> files, char leaderchoice) : Tournament(files), leaderChoice(leaderchoice)
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

			vector<int> game_results = game->getResults();

			cout << "GangA:\t";
			cout << game_results[0] << " years\t";

			cout << "GangB:\t";
			cout << game_results[1] << " years\n\n\n";

			results[j].name = combinations[j];
			results[j].sentences.resize(combinations.size());

			results[i].sentences[j] = game_results[0];
			results[j].sentences[i] = game_results[1];

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

		cout << shortenStrategyList(results[i].name) << "\t";
		cout << results[i].total << "\n";
	}

}