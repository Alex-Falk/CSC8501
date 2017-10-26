#include "GangGame.h"
#include "Gang.h"
#include "Strategy.h"
#include "GangMember.h"
#include "GangStrategy.h"
#include "StrategyGenerator.h"
#include <fstream>

GangGame::GangGame(string combinationA, string combinationB)
{	// Initialise the GangGame class with a combination of strategies for GangA and another combiation for Gang B
	string strategiesA[5];
	string strategiesB[5];

	// Separate the string which has multiple strategies separated by a space into an array of strings, each with one strategy
	for (int i = 0; i < 5; ++i)
	{
		strategiesA[i] = combinationA.substr(0, combinationA.find_first_of(" "));
		combinationA = combinationA.substr(combinationA.find_first_of(" ")+1);

		strategiesB[i] = combinationB.substr(0, combinationB.find_first_of(" "));
		combinationB = combinationB.substr(combinationB.find_first_of(" ")+1);
	}

	gangA = new Gang(strategiesA[0], strategiesA[1], strategiesA[2], strategiesA[3], strategiesA[4]);
	gangB = new Gang(strategiesB[0], strategiesB[1], strategiesB[2], strategiesB[3], strategiesB[4]);

}

GangGame::GangGame(string givenstrat, vector<string> strategies)
{	// Initialise the GangGame class with one given class and randomly the strategies for the 9 other Prisnoers in the game.
	gangA = new Gang(givenstrat, strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()]);
	gangB = new Gang(strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()]);
}

GangGame::~GangGame()
{
	delete A;
	A = nullptr;

	delete B;
	B = nullptr;
}

void GangGame::find_outcome(int iteration)
{	// Find the decision each prisnoer makes and determine the outcome and their sentence according to this
	vector<Decision> decisionsA = gangA->get_gang_decisions(iteration);
	vector<Decision> decisionsB = gangB->get_gang_decisions(iteration);
	
	int betrays_A = 0, betrays_B = 0;

	for (int i = 0; i < 5; ++i) 
	{
		if (decisionsA[i] == Decision::BETRAY) { betrays_A++; }
		if (decisionsB[i] == Decision::BETRAY) { betrays_B++; }
	}

	GangMember::Outcome gangA_outcome;
	GangMember::Outcome gangB_outcome;

	if (betrays_A == 5 && betrays_B == 5)
	{
		gangA_outcome = GangMember::Z;
		gangB_outcome = GangMember::Z;
	}
	else if (betrays_A == 0 && betrays_B == 0)
	{
		gangA_outcome = GangMember::W;
		gangB_outcome = GangMember::W;
	}
	else if (betrays_A == 5 && betrays_B == 0)
	{
		gangA_outcome = GangMember::Y;
		gangB_outcome = GangMember::X;
	}
	else if (betrays_A == 0 && betrays_B == 5)
	{
		gangA_outcome = GangMember::X;
		gangB_outcome = GangMember::Y;
	}
	else if (betrays_A == betrays_B)
	{
		gangA_outcome = GangMember::C;
		gangB_outcome = GangMember::C;
	}
	else if (betrays_A > betrays_B)
	{
		gangA_outcome = GangMember::A;
		gangB_outcome = GangMember::B;
	}
	else if (betrays_A < betrays_B)
	{
		gangA_outcome = GangMember::B;
		gangB_outcome = GangMember::A;
	}

	gangA->sentence_gang(gangA_outcome);
	gangB->sentence_gang(gangB_outcome);
}

void GangGame::run(int iterations,method mthd)
{	// Runs one game with a given number of iterations and given method of spy selection

	vector<string> stratsA = gangA->return_strats();
	vector<string> stratsB = gangB->return_strats();

	int nrspygames = 10;
	vector<int> spygames;

	// Set up a list of games which will have at least one spy in them
	for (int i = 0; i < nrspygames; ++i)
	{
		int rand_iteration = rand() % (iterations - i);
		if (std::find(spygames.begin(), spygames.end(), rand_iteration) != spygames.end())
		{
			spygames.push_back(iteration - i);
		}
		else
		{
			spygames.push_back(rand_iteration);
		}
	}

	// Loop through all the iterations and calculate the results
	for (int i = 0; i < iterations; i++)
	{
		bool has_effect = false;
		// Check if this iteration is supposed to be a game with a spy, and if so run the spyGame method
		if (std::find(spygames.begin(), spygames.end(), i) != spygames.end())
		{
			int rand_gang = rand() % 3;
			
			switch (rand_gang)
			{
			case 0:	// Only gang A gets a spy
				has_effect = spyGame(true, false, mthd);
				break;
			case 1:	// Only gang B gets a spy
				has_effect = spyGame(false, true, mthd);
				break;
			case 2:	// Both gangs get a spy
				has_effect = spyGame(true, true, mthd);
				break;
			}
		}
		// Otherwise (or if no spy was exposed) find the outcome of the game
		if (!has_effect) {
			find_outcome(i);
		}

	}

	totalResults = new Matrix<int>(8, 2);

	totalResults->set_element(0, 0, gangA->get_allw());
	totalResults->set_element(1, 0, gangA->get_allx());
	totalResults->set_element(2, 0, gangA->get_ally());
	totalResults->set_element(3, 0, gangA->get_allz());
	totalResults->set_element(4, 0, gangA->get_alla());
	totalResults->set_element(5, 0, gangA->get_allb());
	totalResults->set_element(6, 0, gangA->get_allc());
	totalResults->set_element(7, 0, gangA->get_scores());
	totalResults->set_element(0, 1, gangB->get_allw());
	totalResults->set_element(1, 1, gangB->get_allx());
	totalResults->set_element(2, 1, gangB->get_ally());
	totalResults->set_element(3, 1, gangB->get_allz());
	totalResults->set_element(4, 1, gangA->get_alla());
	totalResults->set_element(5, 1, gangA->get_allb());
	totalResults->set_element(6, 1, gangA->get_allc());
	totalResults->set_element(7, 1, gangB->get_scores());
}

bool GangGame::spyGame(bool spy_A, bool spy_B, method mthd)
{	// This runs if a game has a spy and will follow the required logic and sentencing
	// Set up spies
	if (spy_A) { gangA->giveSpy(); }
	if (spy_B) { gangB->giveSpy(); }

	bool has_effect = true;

	// Run spy selection logic to see if the leader can "find" the Spy
	int spyA_result = gangA->findSpy(mthd);
	int spyB_result = gangB->findSpy(mthd);

	// These outcomes determine what will happen and who will get sentenced
	switch (spyA_result)
	{
	case 0:	// SPY IN A WAS NOT FOUND
		switch (spyB_result)
		{
		case 0: // SPY IN B WAS NOT FOUND
			has_effect = false;
			break;
		case 1: // SPY IN B WAS FOUND, NO SWITCH
			gangA->add_scores(5);
			gangB->add_scores(0);
			break;
		case 2: // SPY IN B WAS FOUND, SWITCH
			gangA->add_scores(5);
			gangB->add_scores(2);
			break;
		}
	case 1: // SPY IN A WAS FOUND, NO SWITCH
		if (spyB_result == 0)	
		{	// SPY IN B WAS NOT FOUND
			gangA->add_scores(0);
			gangB->add_scores(5);
		}
		else 
		{	// SPY IN B WAS FOUND
			gangA->add_scores(6);
			gangB->add_scores(6);
		}
		break;
	case 2: // SPY IN A WAS FOUND, NO SWITCH
		if (spyB_result == 0) 
		{	// SPY IN B WAS NOT FOUND
			gangA->add_scores(2);
			gangB->add_scores(5);
		}
		else 
		{	// SPY IN B WAS FOUND
			gangA->add_scores(6);
			gangB->add_scores(6);
		}
		break;
	}

	return has_effect;
}

Gang * GangGame::getGangA()
{
	return gangA;
}

Gang * GangGame::getgangB()
{
	return gangB;
}


