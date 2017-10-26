#include "GlobalFunctions.h"
#include "Tournament.h"
#include "GangTournament.h"
#include "StrategyGenerator.h"
#include "GangStrategyGenerator.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void runTournament(Tournament& t)
{

	t.runTournament();
	t.printResults();

	Tournament::result winner = t.findWinner();

	cout << "\nThe Winning combination is: " << shortenStrategyList(winner.name) << " with a total sentence of " << winner.total << " years per gang member\n";
}

void generateStrategies(StrategyGenerator& gen, int NRTOGENERATE)
{
	for (int i = 0; i < NRTOGENERATE; ++i) {
		gen.generateStrategy(10, ("Strategies\\Strategy" + to_string(i) + ".txt"));
		cout << "Generated Strategy: " << ("Strategy" + to_string(i) + ".txt") << "\n";
	}
}

// Takes a string that has 5 strategy names separated by a space
// TODO: Make this work for x amount of strategies
string shortenStrategyList(string strats)
{
	string result = "";

	string strategy;
	string subcombination = strats;

	for (int j = 0; j < 5; ++j)
	{
		strategy = subcombination.substr(0, subcombination.find_first_of(" "));
		subcombination = subcombination.substr(subcombination.find_first_of(" ") + 1);

		int first_nr_idx = strategy.find_first_of("0123456789");
		result = result + strategy.substr(first_nr_idx, strategy.size() - first_nr_idx - 4);
		if (j != 4) { result = result + " "; }
	}

	return result;
}

void readSettings(Settings * settings)
{

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
		default:
			throw runtime_error("Invalid command in Settings file");
			break;
		}
		
	}

	inFile.close();


}
