#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "GangGame.h"
#include "GangTournament.h"
#include "GangStrategyGenerator.h"

using namespace std;

int main() {

	srand(time(NULL));

	char choice;
	int nstrat;
	vector<string> filenames;

	/*
	-------------------------------------------------------------------------------------------------------------------------
	GENERATING STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/
	cout << "Do you want to create strategies? (Y/N) \t";
	cin >> choice;
	if (choice == 'Y') {
		cout << "\n How many strategies do you want to create?\t";
		cin >> nstrat;

		GangStrategyGenerator * gen = new GangStrategyGenerator();
		for (int i = 0; i < nstrat; ++i) {
			gen->generateStrategy(10, ("Strategies\\Strategy" + to_string(i) + ".txt"));

			cout << "Generated Strategy: " << ("Strategy" + to_string(i) + ".txt") << "\n";
		}
	}

	/*
	-------------------------------------------------------------------------------------------------------------------------
	READING IN CUSTOM STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/
	int nstrat_custom, nstrat_gen;
	cout << "\n\n";
	cout << "How many custom strategies do you want to read in?\t";
	cin >> nstrat_custom;
	cout << "\n";

	for (int i = 0; i < nstrat_custom; ++i) {

		string filename;
		cout << "Specify the filename:\t";
		cin >> filename;

		ifstream file("Strategies\\" + filename);
		if (file.good()) { filenames.push_back("Strategies\\" + filename); }
		else { cout << filename << " does not exist\n"; }

		file.close();
	}

	/*
	-------------------------------------------------------------------------------------------------------------------------
	READING IN GENERATED STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/
	cout << "\n";
	cout << "How many generated strategies do you want to read in?\t";
	cin >> nstrat_gen;

	for (int j = 0; j < nstrat_gen; ++j) {
		ifstream file("Strategies\\Strategy" + to_string(j) + ".txt");
		if (file.good()) {
			cout << "Adding Strategy" << to_string(j) << ".txt \n";
			filenames.push_back("Strategies\\Strategy" + to_string(j) + ".txt");
		}
		else { cout << "Strategy" + to_string(j) + ".txt" << " does not exist\n"; }


		file.close();
	}

	cout << "\n" << filenames.size() << " strategies will be used in the tournament \n \n";

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING GANG LEADER CHOICE
	-------------------------------------------------------------------------------------------------------------------------
	*/

	char leaderChoice;
	cout << "Do you wish to \n A: control the Gang Leader's choic \n B: Always swap  \n C: Always stay \n D: Randomly Decide \n";
	cin >> leaderChoice;
	if (leaderChoice != 'A' && leaderChoice != 'B' && leaderChoice != 'C' && leaderChoice != 'D') 
	{
		cout << "Invalid choice, selecting random\n";
		leaderChoice = 'D';
	}
	cout << "\n";

	/*
	-------------------------------------------------------------------------------------------------------------------------
	RUNNING TOURNAMENT
	-------------------------------------------------------------------------------------------------------------------------
	*/

	GangTournament t(filenames,leaderChoice);
	t.runTournament();
	//t.printResults();

	//Tournament::result winner = t.findWinner();

	//cout << "\nThe Winning Strategy is: " << winner.name << " with a total sentence of " << winner.total << " years\n";
	//cout << "The scores against individual strategies of this are: \n";
	//for (int i = 0; i < filenames.size(); ++i) {
	//	if (filenames[i] != winner.name)
	//		cout << filenames[i] << "\t" << winner.sentences[i] << "\n";
	//}


	return 0;
}