#include "GangGame.h"
#include "Gang.h"
#include "Strategy.h"
#include "GangMember.h"
#include "GangStrategy.h"
#include "StrategyGenerator.h"


GangGame::GangGame(string fileA, string fileB, string fileC, string fileD, string fileE)
{
	gangA = new Gang(fileA, fileB, fileC, fileD, fileE);
	gangB = new Gang(fileA, fileB, fileC, fileD, fileE);
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
	Decision * decisionsA = gangA->get_gang_decisions(iteration);
	Decision * decisionsB = gangB->get_gang_decisions(iteration);
	
	int betrays_A, betrays_B;

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
		gangA_outcome = GangMember::W;
	}
	else if (betrays_A == 5 && betrays_B == 0)
	{
		gangA_outcome = GangMember::Y;
		gangA_outcome = GangMember::X;
	}
	else if (betrays_A == 0 && betrays_B == 5)
	{
		gangA_outcome = GangMember::X;
		gangA_outcome = GangMember::Y;
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


