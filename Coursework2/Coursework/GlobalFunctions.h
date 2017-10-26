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

};

string shortenStrategyList(string strats);
void readSettings(Settings * settings);
void runTournament(Tournament& t);
void generateStrategies(StrategyGenerator& gen, int NRTOGENERATE);