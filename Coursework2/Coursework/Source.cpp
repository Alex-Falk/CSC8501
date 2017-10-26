#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "GangGame.h"
#include "GangTournament.h"
#include "GangStrategyGenerator.h"
#include "GlobalFunctions.h"
#include "Matrix.h"
using namespace std;



int main() {

	srand(time(NULL));

	char choice;
	int nstrat;
	vector<string> filenames;

	char settingChoice;

	Settings * settings = new Settings();

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING OUTFILENAME
	-------------------------------------------------------------------------------------------------------------------------
	*/
	string outfilename;
	cout << "Enter an output file name (enter 'default' for the default outfile.txt)\n";
	cin >> outfilename;

	if (outfilename == "default")
	{
		outfilename = "outfile.txt";
	}

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING SETTINGS
	-------------------------------------------------------------------------------------------------------------------------
	*/

	cout << "Choose a way to proceed\n";
	cout << "A: Use the settings.txt file\nB: Manually select settings\nC: Use default settings\n";
	cin >> settingChoice;

	if (settingChoice == 'A') { readSettings(settings); }

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING COURSEWORK
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B')
	{
		int CWchoice;
		cout << "Which Coursework do you want to run?\n1: Coursework1\n2: Coursework2\n";
		cin >> CWchoice;

		(*settings).COURSEWORK = CWchoice;
	}


	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING DETAIL OF RESULTS
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B')
	{
		char detailchoice;
		cout << "How many of the stats do you want to show? \nA: All statistics (for each game show all alloutcomes variables and sentences) \nB: Only The sentences from each game \nC: Only the final Results \nD: Only the Winner\n";
		cin >> detailchoice;

		(*settings).DISPLAY = detailchoice;
	}


	/*
	-------------------------------------------------------------------------------------------------------------------------
	GENERATING STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B')
	{
		cout << "Do you want to create strategies? (Y/N) \t";
		cin >> choice;
		if (choice == 'Y') 
		{
			cout << "\n How many strategies do you want to create?\t";
			cin >> nstrat;
			(*settings).GENERATESTRAT = 'Y';
			(*settings).NRTOGENERATE = nstrat;
		}
		else { (*settings).GENERATESTRAT = 'N'; }
	}


	if ((*settings).GENERATESTRAT == 'Y') 
	{
		if ((*settings).COURSEWORK == 1) 
		{ 
			StrategyGenerator gen; 
			generateStrategies(gen, (*settings).NRTOGENERATE,settings);
		}
		else if ((*settings).COURSEWORK == 2) 
		{ 
			GangStrategyGenerator gen; 
			generateStrategies(gen, (*settings).NRTOGENERATE,settings);
		}
		
	}

	/*
	-------------------------------------------------------------------------------------------------------------------------
	READING IN CUSTOM STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B')
	{
		int nstrat_custom;
		cout << "\n\n";
		cout << "How many custom strategies do you want to read in?\t";
		cin >> nstrat_custom;
		cout << "\n";
		(*settings).NRCUSTOM = nstrat_custom;
	}

	if ((*settings).NRCUSTOM > 0)
	{
		for (int i = 0; i < (*settings).NRCUSTOM; ++i) 
		{
			string filename;
			cout << "Specify the filename:\t";
			cin >> filename;

			string folder;
			if ((*settings).COURSEWORK == 1) { folder = "Strategies\\"; }
			else { folder = "Strategies2\\"; }

			ifstream file(folder + filename);
			if (file.good()) { filenames.push_back(folder + filename); }
			else { cout << filename << " does not exist\n"; }

			file.close();
		}
	}
	

	/*
	-------------------------------------------------------------------------------------------------------------------------
	READING IN GENERATED STRATEGIES
	-------------------------------------------------------------------------------------------------------------------------
	*/
	if (settingChoice == 'B')
	{
		int nstrat_gen;
		cout << "\n";
		cout << "How many generated strategies do you want to read in?\t";
		cin >> nstrat_gen;
		(*settings).NRGENERATED = nstrat_gen;
	}

	if ((*settings).NRGENERATED > 0) 
	{
		string folder;
		if ((*settings).COURSEWORK == 1) { folder = "Strategies\\"; }
		else { folder = "Strategies2\\"; }

		for (int j = 0; j < (*settings).NRGENERATED; ++j) 
		{
			ifstream file(folder + "Strategy" + to_string(j) + ".txt");
			if (file.good()) 
			{
				cout << "Adding Strategy" << to_string(j) << ".txt \n";
				filenames.push_back(folder + "Strategy" + to_string(j) + ".txt");
			}
			else { cout << "Strategy" + to_string(j) + ".txt" << " does not exist\n"; }
			file.close();
		}
	}

	cout << "\n" << filenames.size() << " strategies will be used in the tournament \n \n";

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING NUMBER OF SPYGAMES
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B' && (*settings).COURSEWORK == 2)
	{
		int spychance;
		cout << "What percentage of games should have spies (enter just the number)\t";
		cin >> spychance;
		cout << "\n";
		
		(*settings).SPYCHANCE = spychance;
	}

	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING NUMBER OF ITERATIONS
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B')
	{
		int iterations;
		cout << "How many iterations should each game have?\t";
		cin >> iterations;
		cout << "\n";

		(*settings).ITERATIONS = iterations;
	}


	/*
	-------------------------------------------------------------------------------------------------------------------------
	CHOOSING GANG LEADER CHOICE
	-------------------------------------------------------------------------------------------------------------------------
	*/

	if (settingChoice == 'B' && (*settings).COURSEWORK == 2)
	{
		char leaderChoice;
		cout << "Do you wish to \n A: control the Gang Leader's choice \n B: Always swap  \n C: Always stay \n D: Randomly Decide \n";
		cin >> leaderChoice;
		if (leaderChoice != 'A' && leaderChoice != 'B' && leaderChoice != 'C' && leaderChoice != 'D')
		{
			cout << "Invalid choice, selecting random\n";
			leaderChoice = 'D';
		}
		cout << "\n";

		(*settings).LEADERBEHAVIOUR = leaderChoice;
	}


	/*
	-------------------------------------------------------------------------------------------------------------------------
	SELECTING COMBINATIONS & RUNNING CW1 or CW2
	-------------------------------------------------------------------------------------------------------------------------
	*/

	system("CLS");

	if ((*settings).COURSEWORK == 1)
	{ 
		Tournament t(filenames,(*settings).DISPLAY); 
		runTournament(t, outfilename, settings);
	}
	else if ((*settings).COURSEWORK == 2) 
	{
		GangTournament t(filenames, (*settings).LEADERBEHAVIOUR, (*settings).DISPLAY);
		if (settingChoice == 'B')
		{
			char comboChoice;
			cout << "Do You want to generate a new strategy combinations file? (Y/N)\n";
			cin >> comboChoice;
			cout << "\n";
			switch (comboChoice)
			{
			case 'Y':
			case 'y':
				int ncombo;
				cout << "How many do you want to generate?\n";
				cin >> ncombo;
				cout << "\n";
				(*settings).NRCOMBOS = ncombo;
				(*settings).GENERATECOMBOS = comboChoice;
				break;
			}
		}

		switch ((*settings).GENERATECOMBOS)
		{
		case 'Y':
		case 'y':
			t.generateCombinations((*settings).NRCOMBOS);
			break;
		}
		t.readCombinationFile();

		runTournament(t, outfilename, settings);
	}
		
	return 0;
}

