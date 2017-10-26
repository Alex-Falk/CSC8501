#include "GlobalFunctions.h"
#include "Tournament.h"
#include "GangTournament.h"
#include "StrategyGenerator.h"
#include "GangStrategyGenerator.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string shortenStrategyList(string strats)
{	// Takes a string which has 1 or more strategy file names and shortens it to just the number of strategy. This only works if the Filenames are set like they are generated : "Strategy" + Number.
	string result = "";

	string strategy;
	string subcombination = strats;

	// Finds how many strategy names there are separated by spaces
	int size = std::count(strats.begin(), strats.end(), ' ') + 1;

	// Loop through number of strategies
	for (int j = 0; j < size; ++j)
	{
		// the first strategy name is from the start of the string to the first space
		strategy = subcombination.substr(0, subcombination.find_first_of(" "));
		// set the string that is checked to be a substring that excludes the first strategy
		subcombination = subcombination.substr(subcombination.find_first_of(" ") + 1);

		// Finds where the number is by finding a y (end of the word Strategy)
		int first_nr_idx = strategy.find_first_of("y") + 1;
		
		// If it does not find a Y in the strategy name, then print out the entire strategy name instead... can't shorten.
		if (first_nr_idx != string::npos){ result = result + strategy.substr(first_nr_idx, strategy.size() - first_nr_idx - 4); }
		else {	result = result + strategy;}
		// set the result to be a string with just the numbers of the strategies
		
		if (j != size) { result = result + " "; }
	}

	return result;
}

void readSettings(Settings * settings)
{	// Reads in the settings file and assigns the Setting variables
	ifstream inFile;
	inFile.open("Settings.txt");

	int i = 0;
	while (!inFile.eof()) {
		string line;
		getline(inFile, line);
		string setting = line.substr(0, line.find_first_of(" "));
		string value = line.substr(line.find_first_of(" ") + 1);

		switch (setting[0])
		{
		case 'A':
			(*settings).COURSEWORK = stoi(value);
			break;
		case 'B':
			(*settings).GENERATESTRAT = value[0];
			break;
		case 'C':
			(*settings).NRTOGENERATE = stoi(value);
			break;
		case 'D':
			(*settings).NRCUSTOM = stoi(value);
			break;
		case 'E':
			(*settings).NRGENERATED = stoi(value);
			break;
		case 'F':
			(*settings).LEADERBEHAVIOUR = value[0];
			break;
		case 'G':
			(*settings).GENERATECOMBOS = value[0];
			break;
		case 'H':
			(*settings).NRCOMBOS = stoi(value);
			break;
		case 'I':
			(*settings).DISPLAY = value[0];
			break;
		case 'J':
			(*settings).SPYCHANCE = stoi(value);
			break;
		case 'K':
			(*settings).ITERATIONS = stoi(value);
			break;
		default:
			throw runtime_error("Invalid command in Settings file ");
			break;
		}
	}
	inFile.close();
}

void runTournament(Tournament& t, string outfilename, Settings * settings)
{	// Runs a tournament (or GangTournament with a given output filename and the chosen settings
	t.runTournament(outfilename, settings);

	if ((*settings).DISPLAY != 'D')
	{
		t.printResults();
		t.printResults_toFile(outfilename);
	}


	// Print out the winning strategy (or strategy combination)
	Tournament::result winner = t.findWinner();
	cout << "\nThe Winning combination is: " << shortenStrategyList(winner.name) << " with a total sentence of " << winner.total << " years per gang member\n";

}

void generateStrategies(StrategyGenerator& gen, int NRTOGENERATE, Settings * settings)
{	// Generates a set of strategies (or GangStrategies)
	string folder;
	if ((*settings).COURSEWORK == 1) { folder = "Strategies\\"; }
	else { folder = "Strategies2\\"; }

	for (int i = 0; i < NRTOGENERATE; ++i) {
		gen.generateStrategy(10, (folder + "Strategy" + to_string(i) + ".txt"));
	}
}


