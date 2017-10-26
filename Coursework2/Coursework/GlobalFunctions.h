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

string shortenStrategyList(string strats);
void readSettings(Settings * settings);
void runTournament(Tournament& t,string outfilename, Settings * settings);
void generateStrategies(StrategyGenerator& gen, int NRTOGENERATE,Settings * settings);