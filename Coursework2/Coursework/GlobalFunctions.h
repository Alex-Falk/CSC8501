#pragma once
#include <string>

using namespace std;

class Tournament;
class StrategyGenerator;

struct Settings {
	int COURSEWORK = 2;
	char GENERATESTRAT = 'Y';
	int NRTOGENERATE = 10;
	int NRCUSTOM = 0;
	int NRGENERATED = 10;
	char LEADERBEHAVIOUR = 'B';
	char GENERATECOMBOS = 'Y';
	int NRCOMBOS = 10;
	char DISPLAY = 'A';
	int SPYCHANCE= 10;
	int ITERATIONS = 200;

};

string shortenStrategyList(string strats);												// Takes a string which has 1 or more strategy file names and shortens it to just the number of strategy
void readSettings(Settings * settings);													// Reads in the settings file and assigns the Setting variables
void runTournament(Tournament& t,string outfilename, Settings * settings);				// Runs a tournament (or GangTournament with a given output filename and the chosen settings
void generateStrategies(StrategyGenerator& gen, int NRTOGENERATE,Settings * settings);	// Generates a set of strategies (or GangStrategies)