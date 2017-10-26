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

void GangTournament::runTournament(string filename, Settings * settings)
{
	ofstream outFile;
	outFile.open(filename);
	int gamecounter = 0;
	int iterations = (*settings).ITERATIONS;
	int spygames = iterations / (*settings).SPYCHANCE;
	for (int i = 0; i < combinations.size(); ++i)
	{
		int totalA = 0, totalB = 0;
		results[i].name = combinations[i];
		results[i].sentences.resize(combinations.size());

		for (int j = i; j < combinations.size(); j++)
		{
			gamecounter++;
			GangGame * game = new GangGame(combinations[i], combinations[j]);

			method mthd = method::RANDOM;
			switch (leaderChoice)
			{
			case 'A':
				mthd = method::CUSTOM;
				break;
			case 'B':
				mthd = method::SWAP;
				break;
			case 'C':
				mthd = method::STAY;
				break;
			case 'D':
				mthd = method::RANDOM;
				break;
			}

			game->run(iterations,spygames, mthd);

			Matrix<int> * game_results = game->getResults();
			vector<int> spy_results = game->get_spyResults();

			results[j].name = combinations[j];
			results[j].sentences.resize(combinations.size());

			results[i].sentences[j] = game_results->get_element(7, 0);
			results[j].sentences[i] = game_results->get_element(7, 1);
			
			

			switch (DISPLAY)
			{
			case 'A':
				printFull(game, gamecounter, game_results, spy_results, cout);
				printFull(game, gamecounter, game_results, spy_results, outFile);
				break;
			case 'B':
				printHalf(game, gamecounter, game_results, spy_results, cout);
				printHalf(game, gamecounter, game_results, spy_results, outFile);
				break;
				
			}

			delete game;
			delete game_results;
		}

		for (int k = 0; k < results.size(); ++k)
		{	// Count final scores for each strategy
			results[k].total = std::accumulate(results[k].sentences.begin(), results[k].sentences.end(), 0);
		}

	}
	outFile.close();
}

ostream& GangTournament::printFull(GangGame* game, int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream& ostr)
{
	ostr << "\n------------------------------------------------------------------------------------------------\n";
	ostr << "Game " << gamecounter << "\n\n";
	ostr << "\n" << *(game->getGangA()) << "\n" << "vs.\n" << *(game->getgangB()) << "\n\n";
	ostr << "A: w:" << game_results->get_element(0, 0) << " x:" << game_results->get_element(1, 0) << " y:" << game_results->get_element(2, 0) << " z:" << game_results->get_element(3, 0)
		<< " a:" << game_results->get_element(4, 0) << " b:" << game_results->get_element(5, 0) << " c:" << game_results->get_element(6, 0) << " sentence:" << game_results->get_element(7, 0) << "\n";
	ostr << "B: w:" << game_results->get_element(0, 1) << " x:" << game_results->get_element(1, 1) << " y:" << game_results->get_element(2, 1) << " z:" << game_results->get_element(3, 1)
		<< " a:" << game_results->get_element(4, 1) << " b:" << game_results->get_element(5, 1) << " c:" << game_results->get_element(6, 1) << " sentence:" << game_results->get_element(7, 1) << "\n";
	ostr << "\n";
	ostr << "Spy Outcomes: \n" << "Iterations with: \tSpy only in A: " << spy_results[0] << "\tSpy only in B: " << spy_results[1] << "\tSpies in both: " << spy_results[2] << "\n";
	ostr << "out of which:\t\t" << spy_results[3] << " found in A wit switching\t\t" << spy_results[4] << " found in A without switching\n";
	ostr << "\t\t\t" << spy_results[5] << " found in B with switching\t\t" << spy_results[6] << " found in B without switching\n";
	ostr << "\t\t\t" << spy_results[7] << " found in both\t\t" << spy_results[8] << " not found at all\n";

	return ostr;
}

ostream& GangTournament::printHalf(GangGame* game, int gamecounter, Matrix<int> * game_results, vector<int> spy_results, ostream& ostr)
{
	ostr << "\n------------------------------------------------------------------------------------------------\n";
	ostr << "Game " << gamecounter << "\n\n";
	ostr << "\n" << *(game->getGangA()) << "\n" << "vs.\n" << *(game->getgangB()) << "\n\n";
	ostr << "A: sentence: " << game_results->get_element(7, 0) << "\n";
	ostr << "B: sentence: " << game_results->get_element(7, 1) << "\n";
	ostr << "\n";

	return ostr;
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
	cout << "\n------------------------------------------------------------------------------------------------\n\n";
	for (int i = 0; i < results.size(); ++i)
	{
		cout << "Combination of strategies: ";

		cout << shortenStrategyList(results[i].name) << "\t"  ;
		cout << results[i].total << " years\n";
	}
	cout << "\n------------------------------------------------------------------------------------------------\n";

}

void GangTournament::printResults_toFile(string filename)
{
	ofstream outFile;
	outFile.open(filename, std::ios::app);

	outFile << "\n------------------------------------------------------------------------------------------------\n\n";
	for (int i = 0; i < results.size(); ++i)
	{
		outFile << "Combination of strategies: ";

		outFile << shortenStrategyList(results[i].name) << "\t";
		outFile << results[i].total << "\n";
	}
	outFile << "\n------------------------------------------------------------------------------------------------\n";

	result winner = findWinner();

	outFile << "\nThe Winning combination is: " << shortenStrategyList(winner.name) << " with a total sentence of " << winner.total << " years per gang member\n";


	outFile.close();
}
