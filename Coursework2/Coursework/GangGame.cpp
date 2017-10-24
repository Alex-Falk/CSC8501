#include "GangGame.h"
#include "Gang.h"
#include "Strategy.h"
#include "GangMember.h"
#include "GangStrategy.h"
#include "StrategyGenerator.h"


GangGame::GangGame(string givenstrat, vector<string> strategies)
{
	gangA = new Gang(givenstrat, strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()]);
	gangB = new Gang(givenstrat, strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()], strategies[rand() % strategies.size()]);
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

void GangGame::run(int iterations)
{
	vector<string> stratsA = gangA->return_strats();
	vector<string> stratsB = gangB->return_strats();

	cout << stratsA[0] << "\t" << stratsA[1] << "\t" << stratsA[2] << "\t" << stratsA[3] << "\t" << stratsA[4] << "\n";
	cout << "vs.\n";
	cout << stratsB[0] << "\t" << stratsB[1] << "\t" << stratsB[2] << "\t" << stratsB[3] << "\t" << stratsB[4] << "\n";

	for (int i = 0; i < iterations; i++)
	{
		find_outcome(i);
	}

	totalresults.push_back(gangA->get_scores());
	totalresults.push_back(gangB->get_scores());

}


